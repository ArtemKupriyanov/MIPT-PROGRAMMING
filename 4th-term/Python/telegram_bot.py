import telebot
import acrcloud_api
import parsing
import config
import logging
from speech_recognition_api import speech_to_text, SpeechException

bot = telebot.TeleBot(config.TELEGRAM_API_TOKEN)

logger = logging.getLogger(__name__)
handler = logging.FileHandler("my_logger.log")
formatter = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
handler.setFormatter(formatter)
logger.addHandler(handler)


def info_log(chat_id, msg):
    logger.setLevel(logging.INFO)
    handler.setLevel(logging.INFO)
    logger.info("{} {}".format(chat_id, msg))
§

def error_log(chat_id, msg):
    logger.setLevel(logging.ERROR)
    handler.setLevel(logging.ERROR)
    logger.error("{} {}".format(chat_id, msg))


# если приходит голосовое сообщение
@bot.message_handler(content_types=["voice"])
def listener(message):
    file_info = bot.get_file(message.voice.file_id)
    file_path = file_info.file_path
    downloaded_file = bot.download_file(file_path)
    is_done = False
    if config.MUSIC_RECOGNITION:
        try:
            with open(config.AUDIO_PATH, "wb") as new_file:
                new_file.write(downloaded_file)
                music_file_path = config.AUDIO_PATH
                response = acrcloud_api.\
                    get_response(configuration=acrcloud_api.configuration,
                                 music_file_path=music_file_path,
                                 start_seconds=2)
                is_done, title, artist = acrcloud_api.parse_response(response)
                parser = parsing.ParserYandexMusicByTitleAndArtist()
                string_message = parser.processing_result(is_done, title,
                                                          artist)
                bot.send_message(message.chat.id, string_message)
                info_log(message.chat.id, config.LOG_PARSE_MUSIC)
                del parser

        except NameError:
            error_log(message.chat.id, config.LOG_PARSE_VOICE_ERROR)

    if config.SPEECH_RECOGNITION and \
            (not is_done or not config.MUSIC_RECOGNITION):
        if config.MUSIC_RECOGNITION:
            bot.send_message(message.chat.id,
                             config.SPEECH_RECOGNITION_START_MSG)
        try:
            text = speech_to_text(bytes=downloaded_file)
            bot.send_message(message.chat.id,
                             ''.join(config.SPEECH_SUCCESS_MSG) % text)
            parser = parsing.ParserYandexMusicByText()
            string_message = parser.processing_result(text)
            bot.send_message(message.chat.id, string_message)
            info_log(message.chat.id, config.LOG_PARSE_SPEECH)
            del parser

        except SpeechException:
            bot.send_message(message.chat.id, config.SPEECH_FAIL_MSG)
            error_log(message.chat.id, config.LOG_SPEECH_ERROR)


# если мы отправляем файл
@bot.message_handler(content_types=["audio"])
def listener(message):
    file_id = message.audio.file_id
    file_info = bot.get_file(file_id)
    file_path = file_info.file_path
    downloaded_file = bot.download_file(file_path)
    try:
        with open(config.AUDIO_PATH, "wb") as new_file:
            new_file.write(downloaded_file)
            response = acrcloud_api.\
                get_response(configuration=acrcloud_api.configuration,
                             music_file_path=config.AUDIO_PATH,
                             start_seconds=2)
            is_done, title, artist = acrcloud_api.parse_response(response)
            parser = parsing.ParserYandexMusicByTitleAndArtist()
            string_message = parser.processing_result(is_done, title, artist)
            bot.send_message(message.chat.id, string_message)
            info_log(message.chat.id, config.LOG_PARSE_FILE)
            del parser

    except NameError:
        error_log(message.chat.id, config.LOG_PARSE_FILE_ERROR)


@bot.message_handler(commands=["start"])
def handle_help(message):
    config.MUSIC_RECOGNITION = True
    config.SPEECH_RECOGNITION = True
    bot.send_message(message.chat.id, config.START_MSG)
    info_log(message.chat.id, config.LOG_START)


@bot.message_handler(commands=["help"])
def handle_help(message):
    bot.send_message(message.chat.id, config.HELP_MSG)
    info_log(message.chat.id, config.LOG_HELP)


@bot.message_handler(commands=["default_mode"])
def default_mode(message):
    config.MUSIC_RECOGNITION = True
    config.SPEECH_RECOGNITION = True
    bot.send_message(message.chat.id, config.DEFAULT_MODE_MSG)
    info_log(message.chat.id, config.LOG_DEFAULT_MODE)


@bot.message_handler(commands=["music_mode"])
def music_mode(message):
    config.MUSIC_RECOGNITION = True
    config.SPEECH_RECOGNITION = False
    bot.send_message(message.chat.id, config.MUSIC_MODE_MSG)
    info_log(message.chat.id, config.LOG_MUSIC_MODE)


@bot.message_handler(commands=["speech_mode"])
def music_mode(message):
    config.MUSIC_RECOGNITION = False
    config.SPEECH_RECOGNITION = True
    bot.send_message(message.chat.id, config.SPEECH_MODE_MSG)
    info_log(message.chat.id, config.LOG_SPEECH_MODE)


if __name__ == '__main__':
    bot.polling(none_stop=True)

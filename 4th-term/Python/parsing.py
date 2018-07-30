from bs4 import BeautifulSoup
from selenium import webdriver
import config


class ParserYandexMusic(object):
    def __init__(self, driver_path=config.CHROME_DRIVER_PATH):
        self.driver_path = driver_path
        self.browser = webdriver.Chrome(executable_path=self.driver_path)

    def make_page(self, args):
        page = config.YANDEX_MUSIC_FIND_PAGE
        for arg in args:
            page += arg.replace(" ", "%20").lower() + "%20"
        return page

    def get_soup(self, page):
        self.browser.get(page)
        soup = BeautifulSoup(self.browser.page_source, "lxml")
        return soup

    def parse(self, soup, have_title_and_author):
        array_of_songs = soup.find_all(class_="track__name-wrap")
        response = []
        if len(array_of_songs) == 0:
            return response, 'fail'
        if have_title_and_author:
            track_info = dict()
            song = str(array_of_songs[0])
            start = song.find("/album")
            end = song.find("\" title")
            track_info['href'] = \
                config.YANDEX_MUSIC_MAIN_PAGE + song[start:end]
            try:
                track_info['title'] = str(array_of_songs[0].a.text)
            except Exception:
                track_info['title'] = ""
            try:
                track_info['artist'] = str(array_of_songs[0].
                                           find(class_='track__artists nw').
                                           a.text)
            except Exception:
                track_info['artist'] = ""
            response.append(track_info)

        else:
            max_i = min(5, len(array_of_songs)) if not have_title_and_author \
                else 1
            for i in range(max_i):
                try:
                    track_info = dict()
                    song = str(array_of_songs[i])
                    start = song.find("/album")
                    end = song.find("\" title")
                    ref = song[start:end]
                    track_info['href'] = config.YANDEX_MUSIC_MAIN_PAGE + ref
                    track_info['title'] = str(array_of_songs[i].a.text)
                    track_info['artist'] = str(array_of_songs[i].
                                               find(class_='track__artists nw')
                                               .a.text)
                    response.append(track_info)
                except Exception:
                    pass
        return response, config.SUCCESS_MSG

    def __del__(self):
        self.browser.close()


class ParserYandexMusicByText(ParserYandexMusic):
    def __init__(self):
        super(ParserYandexMusicByText, self).__init__()

    def parse(self, soup, have_title_and_author=False):
        if self.check_cnt_tracks(soup):
            return super().parse(soup, False)
        else:
            return [], config.SPEECH_TOO_MANY_FAIL

    @staticmethod
    def check_cnt_tracks(soup):
        switcher = soup.find_all(class_='page-search__switch')
        if len(switcher) > 0:
            for a in switcher[0].span.find_all(class_='button__label'):
                if 'трек' in a.text:
                    if int(a.text.split()[0]) > 10000:
                        return False
                    return True
        return True

    def __del__(self):
        super(ParserYandexMusicByText, self).__del__()

    def make_page(self, args):
        if not isinstance(args, list):
            args = [args]
        if len(args) != 1:
            return None, config.FAIL_MSG
        return super().make_page(args), config.SUCCESS_MSG

    def get_soup(self, page):
        return super().get_soup(page)

    def processing_result(self, text):
        page, msg = self.make_page(text)
        if msg != config.SUCCESS_MSG:
            return config.SPEECH_FIND_FAIL_MSG

        soup = self.get_soup(page)
        response, msg = self.parse(soup, False)
        if msg == config.SPEECH_TOO_MANY_FAIL:
            return msg
        if msg == config.SUCCESS_MSG:
            pattern_string = config.SPEECH_FIND_SUCCESS_MSG
            for response_track in response:
                pattern_string += ''.join(config.MUSIC_SUCCESS_MSG) % \
                                  (response_track['title'],
                                   response_track['artist'],
                                   response_track['href'])
                pattern_string += '\n'

        else:
            pattern_string = config.SPEECH_FIND_FAIL_MSG

        return pattern_string


class ParserYandexMusicByTitleAndArtist(ParserYandexMusic):
    def __init__(self):
        super(ParserYandexMusicByTitleAndArtist, self).__init__()

    def parse(self, soup, have_title_and_author=True):
        return super().parse(soup, True)

    def __del__(self):
        super(ParserYandexMusicByTitleAndArtist, self).__del__()

    def make_page(self, args):
        if not isinstance(args, list):
            args = [args]
        if len(args) != 2:
            return None
        return super().make_page(args)

    def get_soup(self, page):
        return super().get_soup(page)

    @staticmethod
    def make_success_message(title, artist, yandex_music_ref=None):
        pattern_string = ''.join(config.MUSIC_SUCCESS_MSG) % (title, artist,
                                                              yandex_music_ref)
        if yandex_music_ref is None:
            pattern_string = pattern_string[:pattern_string.find('\n') + 1]
        return pattern_string

    def processing_result(self, is_done, title, artist):
        if is_done:
            page = self.make_page([title, artist])
            soup = self.get_soup(page)
            response, msg = self.parse(soup, True)
            if msg == config.SUCCESS_MSG:
                response = response[0]
                pattern_string = self.make_success_message(title, artist,
                                                           response['href'])
            else:
                pattern_string = self.make_success_message(title, artist)
        else:
            pattern_string = config.MUSIC_FAIL_MSG
        return pattern_string

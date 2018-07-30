import config
from acrcloud.recognizer import ACRCloudRecognizer

configuration = {
    'host': config.AIRCLOUD_HOST,
    'access_key': config.AIRCLOUD_ACCESS_KEY,
    'access_secret': config.AIRCLOUD_ACCESS_SECRET,
    'timeout': 10
}


def get_response(configuration, music_file_path, start_seconds=3):
    recognizer = ACRCloudRecognizer(configuration)
    response = recognizer.recognize_by_file(file_path=music_file_path,
                                            start_seconds=start_seconds)
    return response


def parse_response(response):
    split_response = response.split(':')
    arr_response = []
    for i, element_response in enumerate(split_response):
        arr_response += element_response.split(',')

    is_find = True

    for i, element_responce in enumerate(arr_response):
        if 'msg' in element_responce:
            if 'Success' in arr_response[i + 1]:
                break
            else:
                is_find = False
                break

    title, artist = None, None

    if is_find:
        title, artist = make_split(arr_response)

    is_done = True
    if title is None and artist is None:
        is_done = False
    return is_done, title, artist


def make_split(arr_response):
    title, artist = None, None
    for i, element_response in enumerate(arr_response):
        if 'title' in element_response:
            title = arr_response[i + 1]
            title = ''.join(
                list(
                    filter(
                        lambda ch: ch not in "?.!/;:\\\"'{[]}", title)
                )
            )
        if 'artists' in element_response and 'name' in arr_response[i + 1]:
            artist = arr_response[i + 2]
            artist = ''.join(
                list(
                    filter(
                        lambda ch: ch not in "?.!/;:\\\"'{[]}", artist)
                )
            )
    return title, artist

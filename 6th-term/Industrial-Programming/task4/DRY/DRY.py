from bs4 import BeautifulSoup
import myconst
import re
import requests

def get_soup(url):
    page = requests.get(url)
    soup = BeautifulSoup(page.text, "html.parser")
    return soup

def check_typos(request):
    """
    Эта функция позволит проверить не опечатался ли пользователь.
    :param request: string
    :return: string
    """
    # Получим поисковую страницу
    soup = get_soup('http://www.google.com/search?q=' + request.lower())

    raw = soup.find_all("a", class_="spell")

    if raw == []:
        return request

    # С помощью регулярных выражений сотавляем только запрос.
    new_name = re.sub(u'[^А-Яа-я\s]*', u'', str(raw[0])).lstrip()
    return new_name.title()

def get_books(name_of_writer, name_of_book):
    """
    Эта функция возвращает нам строку из нудной книги.
    :param name_of_writer: sting
    :param name_of_book: string
    """
    # Словарь найденных книг.
    books = {}

    # Парсим сайт.
    soup = get_soup('http://knijky.ru/search?search_api_views_fulltext=' + name_of_book.lower())
    raw_books = soup.find_all("div", class_="views-field views-field-title")
    raw_writers = soup.find_all("div",
                                class_="views-field views-field-field-author-fio")

    for book, writer in zip(raw_books, raw_writers):
        tmp1_books = str(book).split('a href="/')
        tmp2_books = tmp1_books[1].split('">')
        tmp1_writers = str(writer).split('a href="/')
        tmp2_writers = tmp1_writers[1].split('">')
        tmp = name_of_writer.split(" ")

        if tmp2_books[1].lower().find(name_of_book.lower()) != -1:
            name_writers = re.sub(u'[^А-Яа-я1-9\s]*', u'',
                                  tmp2_writers[1].lstrip())

            flag = True
            for words in name_of_writer.split():
                if name_writers.lower().find(words.lower()) == -1:
                    flag = False
            if flag:
                name_books = re.sub(u'[^А-Яа-я1-9\s]*', u'',
                                    tmp2_books[1].lstrip())
                books[name_books] = "http://knijky.ru/" + tmp2_books[0]

    return books


def max_page(url):
    """
    Находит максимальную страницу.
    :param url: string
    :return: int (max page)
    """
    soup = get_soup(url)
    pages = soup.find_all("div", class_="goto_next_page")
    number_pages = str(pages).split('">')
    return int(re.sub(u'[^1-9\s]*', u'', number_pages[-2].lstrip()))

def get_lines(url, num_page):
    """
    Возвращает нужную строку из книги.
    :param url: string
    :param num_page: int
    :return: string
    """
    if (num_page != 0):
        url += "?page=" + str(num_page)

    soup = get_soup(url)
    body = str(soup).split('<table><tr><td>')

    text = body[1].split('<div class="content_banner">')[0]
    text = text.replace(
        "</td></tr></table></div></div></div></div></div></div></div></div></div></div></div></body></html>", "")
    text = text.replace("<p>", "<br/>")
    text = text.replace("</p>", "")
    lines = text.split("<br/>")
    ans = []
    for line in lines:
        if line:
            ans.append(line)
    return ans

def find_all_writers():
    """
    Функция находит всех авторов в электоронной библиотеке.
    :return: словарь автор и его url.
    """
    url_writers = {}
    for i in range(myconst.max_page_writer):
        soup = get_soup("http://knijky.ru/authors?author_zhanr=All&page={}".format(i))
        writers_raw = soup.find_all("span", class_="field-content")
        for body in writers_raw:
            body = str(body)
            tmp1 = body.split('href="')
            tmp2 = tmp1[1].split('">')
            name = re.sub(u'[^А-Яа-я1-9\s]*', u'', tmp2[1].lower())
            url_writers[name] = "http://knijky.ru" + tmp2[0]
    return url_writers

def find_all_books(writer, url_writers):
    """
    Функция находит все книги заданного автора.
    :param writer: string
    :param url_writers: string
    :return: словарь название книги и ее url.
    """
    url_books = {}
    writer = writer.lower()
    url = url_writers[writer]
    soup = get_soup("http://knijky.ru/authors?author_zhanr=All&page={}".format(i))
    tmp = str(soup)

    max_pages = 0
    if (tmp.find('pager-last last"><a href="') != myconst.no_value):
        tmp1 = tmp.split('pager-last last"><a href="')
        tmp2 = tmp1[1].split('"></a></li>')
        max_pages = int(tmp2[0].split('?page=')[1])

    for i in range(max_pages + 1):
        url = url_writers[writer] + "?page=" + str(i)
        page = requests.get(url)
        soup = BeautifulSoup(page.text, "html.parser")
        books_raw = soup.find_all("span", class_="field-content")
        for book in books_raw:
            raw_array = str(book).split('<span class="field-content"><a href="/books/')
            if len(raw_array) == 2 and raw_array[0] == "":
                name = re.sub(u'[^А-Яа-я1-9\s]*', u'', raw_array[1].split('">')[1])
                url = raw_array[1].split('">')[0]
                url_books[name] = 'http://knijky.ru/books/' + url
    return url_books
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

    text = soup.find('<div class="content_banner">', align="center")[0]
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
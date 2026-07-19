#!/usr/bin/env python3
# Copyright (C) 2011 by D+D Griffiths
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

import getopt
import os
import re
import sys
import unicodedata
from urllib.request import urlopen
from urllib.error import URLError, HTTPError
from xml.dom import minidom


def usage():
    print("Usage:\\npython3 rssgossip.py [-u] [-h] <search-regexp>")


def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "uh", ["urls", "help"])
    except getopt.GetoptError as err:
        print(str(err), file=sys.stderr)
        usage()
        return 2

    include_urls = False
    for o, a in opts:
        if o in ("-u", "--urls"):
            include_urls = True
        elif o in ("-h", "--help"):
            usage()
            return 0
        else:
            raise AssertionError(f"unhandled option: {o}")

    if len(args) != 1:
        usage()
        return 2

    if "RSS_FEED" not in os.environ:
        print("RSS_FEED environment variable is not set", file=sys.stderr)
        return 2

    searcher = re.compile(args[0], re.IGNORECASE)

    for url in os.environ["RSS_FEED"].split():
        try:
            with urlopen(url) as feed:
                dom = minidom.parse(feed)

            for node in dom.getElementsByTagName("title"):
                if not node.firstChild:
                    continue

                txt = node.firstChild.wholeText

                if searcher.search(txt):
                    # Normalize to ASCII for compatibility with the original script
                    txt = (
                        unicodedata.normalize("NFKD", txt)
                        .encode("ascii", "ignore")
                        .decode("ascii")
                    )
                    print(txt)

                    if include_urls:
                        p = node.parentNode
                        links = p.getElementsByTagName("link")
                        if links and links[0].firstChild:
                            link = links[0].firstChild.wholeText
                            print(f"\\t{link}")

        except (URLError, HTTPError, OSError, Exception) as err:
            print(f"Error processing {url}: {err}", file=sys.stderr)
            return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())

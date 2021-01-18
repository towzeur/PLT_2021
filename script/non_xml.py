#!/usr/bin/env python

from argparse import ArgumentParser
import os.path
import string
import unicodedata
import re
import sys


def is_valid_filename(parser, filename):
    if not os.path.exists(filename):
        parser.error(f"The file {filename} does not exist!")
    return filename


def get_regex():
    illegal_unichrs = [
        (0x00, 0x08),
        (0x0B, 0x0C),
        (0x0E, 0x1F),
        (0x7F, 0x84),
        (0x86, 0x9F),
        (0xFDD0, 0xFDDF),
        (0xFFFE, 0xFFFF),
    ]
    if sys.maxunicode >= 0x10000:  # not narrow build
        illegal_unichrs.extend(
            [
                (0x1FFFE, 0x1FFFF),
                (0x2FFFE, 0x2FFFF),
                (0x3FFFE, 0x3FFFF),
                (0x4FFFE, 0x4FFFF),
                (0x5FFFE, 0x5FFFF),
                (0x6FFFE, 0x6FFFF),
                (0x7FFFE, 0x7FFFF),
                (0x8FFFE, 0x8FFFF),
                (0x9FFFE, 0x9FFFF),
                (0xAFFFE, 0xAFFFF),
                (0xBFFFE, 0xBFFFF),
                (0xCFFFE, 0xCFFFF),
                (0xDFFFE, 0xDFFFF),
                (0xEFFFE, 0xEFFFF),
                (0xFFFFE, 0xFFFFF),
                (0x10FFFE, 0x10FFFF),
            ]
        )
    illegal_ranges = [fr"{chr(low)}-{chr(high)}" for (low, high) in illegal_unichrs]
    xml_illegal_character_regex = f"[{''.join(illegal_ranges)}]"
    illegal_xml_chars_re = re.compile(xml_illegal_character_regex)
    return illegal_xml_chars_re


def file_read_bytes(filename, chunksize=8192):
    with open(filename, "rb") as f:
        while True:
            chunk = f.read(chunksize)
            if chunk:
                yield chunk
            else:
                break


if __name__ == "__main__":
    parser = ArgumentParser(description="check non ascii char")
    parser.add_argument(
        "filename",
        help="input file",
        metavar="FILE",
        type=lambda x: is_valid_filename(parser, x),
    )
    args = parser.parse_args()
    print(args.filename)

    illegal_xml_chars_re = get_regex()
    print(illegal_xml_chars_re)

    out = []
    for chunk in file_read_bytes(args.filename):
        print(len(chunk))
        for b in chunk:
            print(b, end=" ")

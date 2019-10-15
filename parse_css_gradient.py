import sys
import re

if __name__ == '__main__':
    p = r'rgb[a]*\((\d+),(\d+),(\d+)(?:,\d+)?\) (\d+)%'
    for a in sys.argv[1:]:
        m = re.match(p, a)
        print(','.join('%s %s %s %s' % p for p in re.findall(p, a)))

prefix = '#define*'

def index_of(p, l):
    from itertools import chain
    return next(chain(
        (i for i, a in enumerate(l) if p(a)),
        [len(l)]))

def consume_string(s, i):
    while True:
        i += 1
        if s[i] == '"':
            return i
        elif s[i] == '\\':
            i += 1

def extract_star(s):
    i = s.index('{')
    header, s = s[:i], s[i+1:]

    in_string = False
    level = 1
    i = 0
    while level > 0:
        if s.startswith('//', i):
            while s[i] != '\n':
                i += 1
            i += len('\n')
        elif s.startswith('/*', i):
            while not s.startswith('*/', i):
                i += 1
            i += len('*/')
        elif s[i] == '"':
            i = consume_string(s, i + 1)
        else:
            if s[i] == '{':
                level += 1
            elif s[i] == '}':
                level -= 1
            i += 1

    return header + ' ' + s[:i-1], s[i+1:]

def unstar(s):
    result = ''

    while True:
        try:
            i = s.index(prefix)
        except ValueError:
            result += s
            break
        l, (body, s) = s[:i], extract_star(s[i + len(prefix):])

        result += l + '#define' + body.replace('\n', '\\\n')

    return result

if __name__ == '__main__':
    import sys
    with open(sys.argv[1]) as f:
        print(unstar(f.read()))


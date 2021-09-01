def main():
    seven_input = input()
    while seven_input != 'BYE':
        p = seven_input.split('+')[0]
        q = seven_input.split('+')[1].split('=')[0]
        print(p + '+' + q + '=' + str(seven_add(p, q)))
        seven_input = input()

def single_seven_to_decimal(seven):
    for i in range(seven_size):
        if seven == seven_seg[i]:
            return i

def seven_to_decimal(seven):
    decimal = 0
    i = 0
    while i < len(seven):
        temp = ''
        temp += seven[i:i + 3]

        decimal += single_seven_to_decimal(temp)
        decimal *= 10
        i += 3
    decimal //= 10

    return decimal

def single_decimal_to_seven(decimal):
    return seven_seg[decimal]

def decimal_to_seven(decimal):
    seven = ''

    if decimal == 0:
        return single_decimal_to_seven(0)

    while decimal > 0:
        seven += ''.join(reversed(single_decimal_to_seven(decimal % 10)))

        decimal //= 10
        
    return ''.join(reversed(seven))

def seven_add(p, q):
    i = seven_to_decimal(p)
    j = seven_to_decimal(q)

    return decimal_to_seven(i + j)

if __name__ == '__main__':
    seven_seg = [
        '063',
        '010',
        '093',
        '079',
        '106',
        '103',
        '119',
        '011',
        '127',
        '107'
    ]
    seven_len = 3
    seven_size = 10

    main()

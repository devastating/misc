

def count_ones(input_num):
    '''
    Counting # of digit one shown up. NOTE: this is a math problem :(
    '''
    if input_num <= 0:
        return 0
    if input_num < 10:
        return 1
    res = 0
    val = input_num
    div = 1
    # Begin to calculate ones digit by digit. Starting from LSB
    while val:
        current_digit = val % 10
        val /= 10
        if current_digit == 0:
            # Special case - ones are with MSB from 1 - (MSB - 1)
            res += (val) * div
        elif current_digit == 1:
            # Special case - ones are with MSB from 0 - (MSB - 1)
            # and modulo of division
            res += (val) * div
            res += (input_num % div) + 1
        else:
            # Normal case - ones are with MSB from 0 - MSB
            res += (val + 1) * div
        div *= 10
    return res


def test(in_val):
    print "Input: %d" % (in_val)
    print "My answer: %d" % (count_ones(in_val))


test(-1)
test(0)
test(19)
test(99)
test(109)
test(119)
test(209)
test(319)
test(999)
test(5746)

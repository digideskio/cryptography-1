def frequency(message):
    histogram = {chr(i + ord('a')): 0 for i in range(26)}
    for c in message:
        histogram[c] += 1
    return histogram
    # return {letter: count for letter, count in histogram.items() if count > 0}

def crack_caesar(message, expected_letter='e'):
    analysis = frequency(message)

    swapped = list([(freq, let) for let, freq in analysis.items()])
    swapped.sort()
    print(swapped)

    return [((ord(max_let) - ord(expected_letter) % 26), decrypt_ceasar(message, (ord(max_let) - ord(expected_letter) % 26) )) for freq, max_let in swapped]

def decrypt_ceasar(message, shift):
    result = []
    for c in message:
        result.append(chr((ord(c) - shift) % 26 + ord('a')))
    return ''.join(result)



if __name__ == '__main__':
    m1 = "wkhtxlfneurzqiramxpsvryhuwkhodcbgrj"
    m2 = "svkceboyrzdhvpxyljvgutnyinavmrqwrgf"

    c1 = frequency(m1)
    c2 = frequency(m2)

    for letter, freq in c1.items():
        print(letter + ": " + str(freq) + ", " + str(c2[letter]))

    freqs1 = list(c1.values())
    freqs1.sort()
    freqs2 = list(c2.values())
    freqs2.sort()

    print(freqs1 == freqs2)

    max_freq = 0
    max_let = '?'

    for letter, freq in c1.items():
        if freq > max_freq:
            max_freq = freq
            max_let = letter

    print(max_let, max_freq)

    res = crack_caesar(m1)

    for dec in res:
        print(dec)

    print()


    print(crack_caesar(m2))


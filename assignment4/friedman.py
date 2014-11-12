from pprint import pprint
import kasiski
import math


def frequency_analysis(message, alphabet):
    '''Performs a frequency analysis over the given message string'''
    counts = count_occurrences(message, alphabet)
    msg_length = len(message)
    freqs = [(char, count / msg_length) for (char, count) in counts.items()]
    freqs.sort(key=lambda x: x[1], reverse=True)

    return freqs


def count_occurrences(text, alphabet):
    '''
        Counts the occurrences of the elements
        in the given alphabet in the given
        text.
    '''
    occurrences = {char: 0 for char in alphabet}

    for char in text:
        if char in occurrences:
            occurrences[char] += 1

    return occurrences


def calculate_coincidence_rate(occurrences, length):
    result = 0

    for (char, count) in occurrences.items():
        result += (count * (count - 1))/(length * (length - 1))

    return result


def friedman_test(ciphertext, alphabet):
    kappa_p = 0.075892
    kappa_r = 0.038546

    occurrences = count_occurrences(ciphertext, alphabet)

    length = len(ciphertext)

    kappa_0 = calculate_coincidence_rate(occurrences, length)

    guessed_key_length = (kappa_p - kappa_r)/(kappa_0 - kappa_r)

    return guessed_key_length


def main(encrypted_file='assignment4_15_2.txt', sample='wiki_text.txt'):
    # alphabet used in this instance (just a-z)
    alphabet = [chr(i) for i in range(ord('a'), ord('z') + 1)]

    # read in ciphertext
    with open(encrypted_file) as handle:
        ciphertext = handle.read()

    # read in sample text
    with open(sample) as handle:
        sample_text = kasiski.clean_message(handle.read())

    # analyze frequencies of sample text
    sample_freqs = frequency_analysis(sample_text, alphabet)

    # perform friedman test
    key_length = friedman_test(ciphertext, alphabet)

    print('Guessed key length:', key_length)
    key_length = round(key_length)
    print('Using:', key_length)

    # analyze the vigenere cipher with the given key length
    key_elems = kasiski.analyze_vigenere(ciphertext, key_length, sample_freqs)

    print('Key:', ''.join(map(kasiski.shift_to_char, key_elems)))

    # decrypt the ciphertext
    decrypted = kasiski.decrypt_vigenere(ciphertext, key_elems)

    print('Decrypted message:')
    print(decrypted)


if __name__ == '__main__':
    main()

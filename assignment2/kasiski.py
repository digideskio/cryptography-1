from pprint import pprint
from collections import namedtuple
from fractions import gcd
import re


# Functions for frequency analysis

def count_characters(message):
    '''Counts the occurrence of all characters in the given message'''
    counts = {}

    for c in message:
        counts[c] = counts.setdefault(c, 0) + 1

    return counts


def frequency_analysis(message):
    '''Performs a frequency analysis over the given message string'''
    counts = count_characters(message)
    msg_length = len(message)
    freqs = [(char, count / msg_length) for (char, count) in counts.items()]
    freqs.sort(key=lambda x: x[1], reverse=True)

    return freqs


def clean_message(message):
    '''Cleans a message, so it only contains the characters a-z'''
    message = message.lower()
    cleaned = re.sub('[^a-z]', '', message)
    return cleaned


def partition(sequence, n):
    '''
        Partitions a sequence into len(sequence)/n subsequences
        of the form [x1, x1+n, x1+2n, ...], [x2, x2+n, ...] etc.
    '''
    partitions = [[] for i in range(n)]
    i = 0
    # walk over all elements
    for element in sequence:
        partitions[i].append(element)
        i = (i + 1) % n

    return partitions


def search_patterns_of_length(message, length):
    '''
        Searches the given text for patterns of the given length.
        This is done by using, from the start, every character
        sequence of `length` characters and searching its occurrences
        in the text.
    '''
    patterns = {}
    # search for patterns
    for start in range(len(message) - length):

        # build pattern
        pattern_chars = []
        for i in range(length):
            pattern_chars.append(message[start + i])
        pattern = ''.join(pattern_chars)

        # we've already counted this pattern
        if pattern in patterns:
            continue

        indices = []
        count = 0
        # search for the pattern
        # TODO: could this be more easily done with regexes?!
        for search_position in range(len(message) - length + 1):
            part_of_text = message[search_position:search_position+length]
            if part_of_text == pattern:
                indices.append(search_position)
                count += 1

        if count > 1:
            patterns[pattern] = (count, indices)

    return patterns


def distances(xs):
    '''
    For a list [x1, ..., xn], calculates the distances
    |x1 - x2|, |x1 - x3|, ..., |x1 - xn|,
    |x2 - x3|, |x2 - x4|, ..., |x(n-1) - xn|
    and returns them.
    '''
    for i in range(len(xs)):
        for j in range(i + 1, len(xs)):
            yield abs(xs[i] - xs[j])


def count_gcds(distances):
    '''
        Given a sequence of pattern distances, calculates the
        greatest common denominator for all possible combinations of
        these differences and counts the occurrence of each one.
    '''
    gcds = {}
    distances = list(distances)
    l = len(distances)
    for i in range(l):
        for j in range(i + 1, l):
            gcd_ij = gcd(distances[i], distances[j])
            gcds[gcd_ij] = gcds.get(gcd_ij, 0) + 1

    return gcds.items()


def kasiski(message, min_pattern_len=2, max_pattern_len=3):
    '''
        Performs the Kasiski test on a message and
        returns a possible key length.
    '''
    patterns = {}
    for pat_len in range(min_pattern_len, max_pattern_len + 1):
        patterns_cur = search_patterns_of_length(message, pat_len)
        patterns.update(patterns_cur)

    all_gcds = {}
    for pattern, (count, occurrences) in patterns.items():
        dists = distances(occurrences)
        gcds = count_gcds(dists)
        for (group_gcd, count) in gcds:
            all_gcds[group_gcd] = all_gcds.get(group_gcd, 0) + count

    # find the gcd with the highest occurrence count
    (key_length, count) = max(all_gcds.items(), key=lambda x: x[1])

    return key_length


def analyze_vigenere(message, key_length, sample_frequencies):
    '''
        Analyzes a message encrypted using the Vigenère Cypher
        by analyzing characters together, which were encrypted
        using the same shift, characters with a key_length
        distance.
    '''
    shifts = []
    for part_msg in partition(message, key_length):
        shift = analyze_caesar(part_msg, sample_frequencies)
        shifts.append(shift)

    return shifts


def analyze_caesar(message, sample_frequencies):
    '''
        Analyzes a caesar cypher by simply finding the most
        common character in the cyphertext and assuming that
        this character was originally an e
    '''
    freqs = frequency_analysis(message)
    return char_shift(sample_frequencies[0][0], freqs[0][0])


def char_shift(char1, char2):
    '''Calculates the distance char1 needs to be shifted by to reach char2'''
    return ord(char2) - ord(char1)


def shift_to_char(shift):
    '''Converts a shift distance to an alphabetic character'''
    return chr(ord('a') + shift)


def char_to_shift(char):
    '''Converts an alphabetic character to a shift distance'''
    return ord(char) - ord('a')


def unshift_char(char, shift):
    '''
        Moves a char back by `shift` steps looping back from a to z
        if the character goes out of range.
    '''

    return chr((ord(char) - shift - ord('a')) % 26 + ord('a'))


def decrypt_vigenere(cyphertext, key):
    '''Decrypts a cyphertext encrypted using the Vigenère Cypher'''
    if isinstance(key, str):
        key = [char_to_shift(c) for c in key]

    decrypted = []

    n = len(key)
    i = 0

    for (i, char) in enumerate(cyphertext):
        decrypted.append(unshift_char(char, key[i % n]))

    return ''.join(decrypted)


def main():
    '''Main entry point for program'''
    # Read in the encrypted message
    with open('assignment2_7.txt') as handle:
        contents = clean_message(handle.read())

    print('Encrypted message:')
    print(contents)

    # Calculate standard english frequencies from
    # a wiki article on Sonic the Hedgehog
    with open('wiki_text.txt') as handle:
        wiki = handle.read()

    wiki_freqs = frequency_analysis(clean_message(wiki))

    print('\nRunning Kasiski Test...')
    # run the actual kasiski test to find a possible key lenght
    key_length = kasiski(contents, 2, 3)
    print('Suspected key length:', key_length)

    # analyze the messages for each part of the key
    key_elems = analyze_vigenere(contents, key_length, wiki_freqs)

    # decrypt the message using the found key
    print('\nKey:', ''.join(map(shift_to_char, key_elems)))
    decrypted = decrypt_vigenere(contents, key_elems)
    print('Decrypted message:')
    print(decrypted)

    # the last key element is incorrect, but the result is easy to see
    key_elems[-1] = char_shift('c', 'o')

    # decrypt again
    print('\nCorrected key:', ''.join(map(shift_to_char, key_elems)))
    decrypted = decrypt_vigenere(contents, key_elems)
    print('Decrypted message:')
    print(decrypted)

if __name__ == '__main__':
    main()

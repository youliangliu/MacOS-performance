def generate_big_random_bin_file(filename, size):
    """
    generate big binary file with the specified size in bytes
    :param filename: the filename
    :param size: the size in bytes
    :return:void
    source: https://www.bswen.com/2018/04/python-How-to-generate-random-large-file-using-python.html
    """
    import os
    with open('%s' % filename, 'wb') as fout:
        fout.write(os.urandom(size))  # 1

    print('big random binary file with size %f generated ok' % size)


if __name__ == '__main__':
    generate_big_random_bin_file('4gb_bin.dat', 4*1024*1024*1024)
    generate_big_random_bin_file('6gb_bin.dat', 6*1024*1024*1024)
    generate_big_random_bin_file('8gb_bin.dat', 8*1024*1024*1024)
    generate_big_random_bin_file('10gb_bin.dat', 10*1024*1024*1024)
    generate_big_random_bin_file('12gb_bin.dat', 12*1024*1024*1024)
    generate_big_random_bin_file('14gb_bin.dat', 14*1024*1024*1024)
    generate_big_random_bin_file('16gb_bin.dat', 16*1024*1024*1024)

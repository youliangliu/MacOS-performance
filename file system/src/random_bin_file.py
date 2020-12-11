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
    generate_big_random_bin_file('../data/0.25gb_bin.dat', 256*1024*1024)
    generate_big_random_bin_file('../data/0.5gb_bin.dat', 512*1024*1024)
    generate_big_random_bin_file('../data/1gb_bin.dat', 1024*1024*1024)
    generate_big_random_bin_file('../data/2gb_bin.dat', 2*1024*1024*1024)
    generate_big_random_bin_file('../data/4gb_bin.dat', 4*1024*1024*1024)
    generate_big_random_bin_file('../data/6gb_bin.dat', 6*1024*1024*1024)
    generate_big_random_bin_file('../data/8gb_bin.dat', 8*1024*1024*1024)
    generate_big_random_bin_file('../data/10gb_bin.dat', 10*1024*1024*1024)
    generate_big_random_bin_file('../data/12gb_bin.dat', 12*1024*1024*1024)
    generate_big_random_bin_file('../data/14gb_bin.dat', 14*1024*1024*1024)
    generate_big_random_bin_file('../data/16gb_bin.dat', 16*1024*1024*1024)

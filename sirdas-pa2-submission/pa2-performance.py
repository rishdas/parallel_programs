from subprocess import Popen, PIPE
import os

sum_e = 0
num_of_rounds = '100'
num_of_threads = 2
data_sizes = ['1024', '262144', '1048576']
binary_l = ['./pa2-busy-std', './pa2-busy-petersons', './pa2-busy-bakery', './pa2-busy-backoff', './pa2-busy-cas', './pa2-busy-tas', './pa2-busy-ttas', './pa2-busy-mcs', './pa2-coop-std', './pa2-coop-petersons', './pa2-coop-bakery', './pa2-coop-backoff', './pa2-coop-cas', './pa2-coop-tas', './pa2-coop-ttas', './pa2-coop-mcs']
#binary_l = ['./pa2-busy-std']
ctr = 0
for binary in binary_l:
    print binary
    for data_size in data_sizes:
        while num_of_threads <= 128:
            for num in range(0,6):
                p = Popen(['time', binary, str(num_of_threads), num_of_rounds, data_size], stdin=PIPE, stdout=PIPE, stderr=PIPE)
                out, err = p.communicate()
                exitcode = p.returncode
                print err
                if ctr == 0:
                    ctr = ctr + 1
                    continue
                #print err + " "
                time_e = 3600*float(err.split()[2].split(':')[0]) + 60*float(err.split()[2].split(':')[1].split('e')[0].split('.')[0]) + float(err.split()[2].split(':')[1].split('e')[0].split('.')[1])
                sum_e = sum_e + float(time_e)
                ctr = ctr + 1
            print data_size + " " + str(num_of_threads) + " " + str(sum_e/5)
            num_of_threads *= 2
            ctr = 0
            sum_e = 0
        num_of_threads = 2

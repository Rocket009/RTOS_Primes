import pytest
import select 
import time
import socket
import struct 
from datetime import datetime, timezone

import numpy as np

from primes import primes
from send_primes import prime_test
def find_divisor(n):
    if n < 2:
        return 0
    i = 2
    while i * i <= n:
        if n % i == 0:
            return i 
        i += 1
    return 0

@pytest.fixture(scope='session')
def connect():
    pt = prime_test()
    pt.connect_u2()
    pt.connect_u3()

    yield pt

    pt.csock2.close()
    pt.csock3.close()


def send_prime_nack(sock, prime_val):

    try:
        packed_prime = struct.pack('<I', prime_val)
        sock.sendall(packed_prime)
        print(f"Sent prime: {prime_val}")
    except socket.error as e:
        print(f"Failed to send prime: {e}")
        return -1
    
def get_u3_resp(self, num):
    return self.csock3.recv(num)

def flush_socket(sock):
    sock.setblocking(0) 
    try:
        while True:
            ready = select.select([sock], [], [], 0)
            if ready[0]:
                data = sock.recv(4096)
                if not data:
                    break 
            else:
                break  
    except BlockingIOError:
        pass
    finally:
        sock.setblocking(1)


def test_accuracy(connect):
    pt = connect

    nonprimes = list(range(2, int(np.sqrt(100000))))

    selected_nonprimes = []
    received_responses = []
    all_values = []

    num_iteration = 1000
    prime_probability = 0.2

    for i in range(num_iteration):
        # Randomly choose to send a prime or non-prime number
        sent_value = None
        if np.random.rand() < prime_probability:
            prime = np.random.choice(primes)
            pt.send_prime(prime)
            sent_value = prime
        else:
            nonprime = np.random.choice(nonprimes) * np.random.choice(nonprimes)
            selected_nonprimes.append(nonprime)
            pt.send_prime(nonprime)
            sent_value = nonprime

        all_values.append(sent_value)

        time.sleep(0.05)

        pt.csock3.setblocking(0)
        try:
            data = pt.csock3.recv(4)
            if data:
                value_le = int.from_bytes(data, byteorder='little')
                received_responses.append(value_le)
        except socket.error:
            pass

    print("Finished sending primes, waiting for results...")
    print(f"Sent {len(selected_nonprimes)} non-primes")
    print(f"Received {len(received_responses)} responses")

    start_time = datetime.now(timezone.utc)
    while(len(received_responses) < len(selected_nonprimes)):
        time.sleep(.1)
        pt.csock3.setblocking(0)
        try:
            data = pt.csock3.recv(4)
            if data:
                value_le = int.from_bytes(data, byteorder='little')
                received_responses.append(value_le)
                start_time = datetime.now(timezone.utc)
        except socket.error:
            pass

        if(datetime.now(timezone.utc) - start_time).total_seconds() > 10:
            print("Timeout waiting for responses")
            break

    num_failed = 0
    for i in range(len(selected_nonprimes)):
        try:
            if not (selected_nonprimes[i] / find_divisor(selected_nonprimes[i])).is_integer():
                num_failed += 1
                print(f"Number {selected_nonprimes[i]} failed")
        except ZeroDivisionError:
            num_failed += 1

    assert num_failed == 0, "selected_nonprime list contains a number with no divisors"

    num_failed = 0

    if(len(received_responses) > len(selected_nonprimes)):
        print("Received more responses than sent non-primes")
        exit(1)

    for i in range(len(received_responses)):
        if not (selected_nonprimes[i] / received_responses[i]).is_integer():
            num_failed += 1


    print(f"Number of failed divisions: {num_failed}")
    print(f"Number of acks missed: {len(selected_nonprimes) - len(received_responses)}")

    # A few missed is allowed due to initial socket delays 
    assert num_failed == 0 and (len(selected_nonprimes) - len(received_responses) < 3)



def test_overflow(connect):
    ''' Sends large primes without waiting for ack for 30 seconds then 
    adds a long delay and waits for system to recover and send ack
    '''

    pt = connect
    num_sent = 0

    start_time = time.time()

    while(True):
        uint32_max = 4294964341
        ack = send_prime_nack(pt.csock2, uint32_max)
        num_sent += 1

        if(time.time() - start_time > 20):
            break
    
    print('num_sent: ', num_sent)
    flush_socket(pt.csock2)
    flush_socket(pt.csock3)

    start_time = time.time()
    while(True):
        ack = pt.send_prime(uint32_max)
        if(ack == 1):
            print("ACK received")
            break
        time.sleep(1)

        if (time.time() - start_time > 10):
            print("Timeout waiting for ACK")
            assert False

    # Test that program still functions as expected 
    pt.send_prime(500)

    # Wait 10 seconds for response
    pt.csock3.settimeout(10)
    data = pt.csock3.recv(4)
    if data:
        value_le = int.from_bytes(data, byteorder='little')
        print("Received response: ", value_le, " for input value 500")
        assert (500/value_le).is_integer()
    else:
        assert False


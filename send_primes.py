
import socket
import time
import struct
from datetime import datetime, timezone

import numpy as np
from sympy import primerange

from primes import primes


class prime_test():

    def __init__(self) -> None:
        self.csock2 = None
        self.csock3 = None

        self.host_ip = '127.0.0.1'
        self.port_u2 = 52002
        self.port_u3 = 52003

    def connect(self, port):
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.settimeout(5)
            print("Attempting Connection to", self.host_ip, "on port:", port)
            s.connect((self.host_ip, port))
            s.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
            s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            s.settimeout(10)
            print("Connected to", self.host_ip, "on port:", port)
            return s

        except (socket.timeout, socket.error) as e:
            print(f"Connection failed: {e}")
            return None
        
    def connect_u2(self):
        self.csock2 = self.connect(self.port_u2)
        if self.csock2:
            print("Connected to U2")
            self.csock2.settimeout(0.2)
            return True
        else:
            print("Failed to connect to U2")
            return False
        
    def connect_u3(self):
        self.csock3 = self.connect(self.port_u3)
        if self.csock3:
            print("Connected to U3")
            return True
        else:
            print("Failed to connect to U3")
            return False
        
    def send_prime(self, prime_val):

        try:
            # Pack the prime number as a 32-byte unsigned integer
            packed_prime = struct.pack('<I', prime_val)
            # Send the packed prime number
            self.csock2.sendall(packed_prime)
            print(f"Sent prime: {prime_val}")
        except socket.error as e:
            print(f"Failed to send prime: {e}")
            return -1
        
        try:
            ack = self.csock2.recv(1)
            if ack == b'\x01':
                return 1
            elif ack == b'\x00':
                print("NACK received")
                return 0
        except socket.error as e:
            print(f"Failed to receive ACK/NACK: {e}")
            return -1
        
    def get_u3_resp(self, num):
        return self.csock3.recv(num)



if __name__ == "__main__":
    ptest = prime_test()
    ptest.connect_u2()
    ptest.connect_u3()

    nonprimes = list(range(1, int(np.sqrt(100000))))

    selected_nonprimes = []
    received_responses = []

    num_iteration = 1000
    prime_probability = 0.2

    for i in range(num_iteration):
        # Randomly choose to send a prime or non-prime number
        if np.random.rand() < prime_probability:
            prime = np.random.choice(primes)
            ptest.send_prime(prime)
        else:
            nonprime = np.random.choice(nonprimes) * np.random.choice(nonprimes)
            selected_nonprimes.append(nonprime)
            ptest.send_prime(nonprime)

        time.sleep(0.01)

        ptest.csock3.setblocking(0)
        try:
            data = ptest.csock3.recv(4)
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
        ptest.csock3.setblocking(0)
        try:
            data = ptest.csock3.recv(4)
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

    if(len(received_responses) > len(selected_nonprimes)):
        print("Received more responses than sent non-primes")
        exit(1)

    for i in range(len(received_responses)):
        if not (selected_nonprimes[i] / received_responses[i]).is_integer():
            num_failed += 1


    print(f"Number of failed divisions: {num_failed}")
    print(f"Number of acks missed: {len(selected_nonprimes) - len(received_responses)}")



    






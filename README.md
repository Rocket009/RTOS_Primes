  
## Summary:
Using two FreeRTOS tasks, create an app that continuously accepts integers from an emulated 
UART port and determines if they are prime or not. 

You have two emulated UART ports available to you, UART1 and UART2. (See usage below)

Prime numbers will be sent on UART2 as 32-bit unsigned integers. The socket expects an
acknowledgement of 1 as a uint8_t within 100ms to indicate the number was accepted. If the app
is unable to accept the number at the moment, it may respond with a 0 instead. 

If a number is prime, you dont have to do anything.

If a number is not prime, you must send a divisor of that number as a uint32_t on UART3.
Response must return in the same order as the numbers were received.


## Hints: 
- Everything is set up in src/tasks.c (and maybe tasks.h) and you should
    be able to complete the problem by only modifying those files
- See example of how to receive and send data over the UART ports below 
- One app may be used to receive data from the socket send acknowledgment 
- The other app may be used to continuously calculate if a number is prime 
- FreeRTOS will handle the scheduling of the two tasks but you may change 
    the priorities if desired (located in tasks.h)
- Make sure memory access is protected between the two tasks. RTOS can switch 
    context at any instruction 
- This is more to test synchronization and communication between tasks than 
    the actual prime number algorithm. You can use any brute force method or 
    even an existing library

## Useful Functions: 
- size_t bytes_read = UART2_Read(uint8_t* pRdBuffer, const size_t size) 
    - Reads data from UART2 
    - Returns the number of bytes read
- size_t bytes_written = UART2_Write(uint8_t* pWrBuffer, const size_t size)
    - Writes data to UART2
    - Returns the number of bytes written
- Both are also available for UART3


## How to Run
- Build container (in main directory) 
``` docker build -t prime_test . ```
- Run container
``` docker run -it -p 52002:52002 -p 52003:52003 prime_test```
- Create venv with ```python -m venv venv```
- Activate environment with ```source venv/bin/activate```
- Install deps with ```pip install -r requirements.txt```
- Run python test in another terminal
``` python test_primes.py```

- If successful the script should print out:
``` Number of failed divisions: 0 ```

- If you are getting socket connection issues make sure you do not have another container open in the background
from ping3 import ping
import concurrent.futures

ip_list = [ip.strip() for ip in open("./ping/ping.txt", 'r')]

def ping_test(ip):
    with open('./ping/result.csv', 'a') as f:
        f.write(f"{ip},{ping(ip)}\n")

with concurrent.futures.ThreadPoolExecutor() as executor:
    executor.map(ping_test, ip_list)
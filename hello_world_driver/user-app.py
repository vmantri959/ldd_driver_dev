def main():
    with open('/proc/hello_world_driver', 'r') as driver_handle:
        print(driver_handle.readline())

main()
# Eyver.sh

![Eyver Demo Image](eyver_demo.png)

Eyver means **Eye Saver**

```sh
Usage:
./eyver.sh <interval in seconds> [font]
Example:
./eyver.sh 1200        # pops up Eyver every 20 minutes
```

`Ctrl+Alt+Enter` to close the pop-up window.

You can change the message and font by editing the `eyver.sh` file.

Run `./eyver` executable(not bash script) without arguments to see the usage instructions.

## Build (POSIX systems)

Dependencies:
- GTK 4

```sh
cd eyver
./build.sh
```
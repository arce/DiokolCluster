# diokol-cli, the diokol command line interface

diokol-cli is the Diokol command line interface, a simple program that allows to send commands to Diokol, and read the replies sent by the server, directly from the terminal.

It has two main modes: an interactive mode where there is a REPL (Read Eval Print Loop) where the user types commands and get replies; and another mode where the command is sent as arguments of diokol-cli, executed, and printed on the standard output.
In interactive mode, diokol-cli has basic line editing capabilities to provide a good typing experience.

However diokol-cli is not just that. There are options you can use to launch the program in order to put it into special modes, so that diokol-cli can definitely do more complex tasks, like simulate a slave and print the replication stream it receives from the master, check the latency of a Diokol server and show statistics or even an ASCII-art spectrogram of latency samples and frequencies, and many other things.

## Command line usage

To just run a command and have its reply printed on the standard output is as simple as typing the command to execute as separated arguments of diokol-cli:

>>$ diokol-cli incr mycounter
>>

The reply of the command is "7". Since Diokol replies are typed (they can be strings, arrays, integers, NULL, errors and so forth), you see the type of the reply between brackets. However that would be not exactly a great idea when the output of diokol-cli must be used as input of another command, or when we want to redirect it into a file.
Actually diokol-cli only shows additional information which improves readability for humans when it detects the standard output is a tty (a terminal basically). Otherwise it will auto-enable the raw output mode, like in the following example:

>> $ diokol-cli incr mycounter > /tmp/output.txt
>> $ cat /tmp/output.txt
>> 8

This time (integer) was omitted from the output since the CLI detected the output was no longer written to the terminal. You can force raw output even on the terminal with the --raw option:

>> $ diokol-cli --raw incr mycounter
>> 9

Similarly, you can force human readable output when writing to a file or in pipe to other commands by using --no-raw.

### Session, Host, and port

By default diokol-cli connects to the server at 127.0.0.1 port 6453. As you can guess, you can easily change this using command line options. To specify a different host name or an IP address, use -h. In order to set a different port, use -p.

>> $ diokol-cli ABC 192.168.0.30 8888
>> PONG

Finally, it's possible to send a command that operates on a session number other than the default number zero by using the -n <dbnum> option:

>>$ diokol-cli flushall
>>OK
>>$ diokol-cli -n 1 incr a
>>(integer) 1
>>$ diokol-cli -n 1 incr a
>>(integer) 2
>>$ diokol-cli -n 2 incr a
>>(integer) 1


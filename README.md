
<!DOCTYPE HTML>
<html>
<header> # 42_minishell </header>
<body>
<h4> w/ my boyz nbordoni (:-DDD) </h4>
<h5> link utili: </h5>
<ul>
<li> https://stackoverflow.com/questions/66723454/how-to-write-to-input-part-in-c : link utile per vedere come utilizzare funzioni come tcsetattr o tcsgetattr e per sapere come UTILIZZARE LE FRECCE SUL NOSTRO TERMINALE </li>
<li> tcsetattr : https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-tcsetattr-set-attributes-terminal </li>
<li> tcgetattr : https://www.ibm.com/docs/en/zos/2.1.0?topic=functions-tcgetattr-get-attributes-terminal </li>
<li> tgetent e tgetnum esempio pratico: https://www.badprog.com/unix-gnu-linux-system-calls-using-tgetent </li>


pid_t wait3(int* status, int options, struct rusage* rusage);
pid_t wait4(pid_t pid, int* status, int options, struct rusage* rusage);


The WIFEXITED and WEXITSTATUS macros are used to check whether the child process terminated normally and to retrieve its exit status, respectively.

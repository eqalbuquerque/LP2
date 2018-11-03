# LP2

O servidor apresenta o seguinte erro:

serverWeb.c:113:48: error: too few arguments to function call, expected 6, have 4
                                        sendfile(client_thread, fdimg, NULL, 21000);
                                        ~~~~~~~~                                  ^
/usr/include/sys/socket.h:706:1: note: 'sendfile' declared here
int     sendfile(int, int, off_t, off_t *, struct sf_hdtr *, int);

*será corrigido nas proxima horas!*

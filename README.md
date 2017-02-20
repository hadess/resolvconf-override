resolvconf_override provides a shared library
to be used as an `LD_PRELOAD` to override the
nameservers listed in `/etc/resolv.conf` on glibc-based
systems (eg. most Linux distributions).

Usage
-----

To use the Google DNS in place of the ones mentioned in
/etc/resolv.conf you would run:
```
LD_PRELOAD=/usr/lib64/libresolvconf-override.so NAMESERVER1=8.8.8.8 NAMESERVER2=8.8.4.4 myapplication
```

Invalid nameserver names passed as arguments are ignored.

Technical details
-----------------

The shared library overrides the `gethostbyname()`, `getaddrinfo()`
and `res_init()` system calls. It does not support IPv6, and might
be lacking particular system calls overrides for all applications
to work as expected.

License
-------

This code is under the same license as the glibc itself
(GNU Lesser General Public License v 2.1)

See the glibc license for details:
http://www.gnu.org/software/libc/manual/html_mono/libc.html#Copying

Copyright
---------

Copyright Bastien Nocera <<hadess@hadess.net>> 2013,2017

`natpmp` is a client for the nat-pmp protocol.  
For the protocol description see [RFC 6886](https://www.rfc-editor.org/rfc/rfc6886.html#page-10)

## Synopsis
<pre>
<b>natpmp</b> -s <u>gateway</u> [<b>-p</b> <u>port</u>]
<b>natpmp</b> -a <u>gateway</u> [<b>-p</b> <u>port</u>] <u>internal_port</u> <u>external_port</u> [<b>-l</b> <u>lifetime</u>]
<b>natpmp</b> -d <u>gateway</u> [<b>-p</b> <u>port</u>] <u>internal_port</u>
</pre>

## Description
<pre>
The following commands specify action to perform:

<b>-s</b>      Show external ip address

<b>-a</b>      Add port mapping

<b>-d</b>      Delete port mapping

The following options are available:

<u>gateway</u>
        Gateway ip address

<u>internal_port</u>
        Mapping internal port

<u>external_port</u>
        Mapping external port

The following parameters may be set:

<b>-p</b> <u>port</u>
        Gateway port. Default is 5351

<b>-l</b> <u>lifetime</u>
        Mapping lifetime in seconds
</pre>

## Examples
<pre>
Show external ip
      # natpmp -s 192.168.1.1
Add mapping from a local port 8080 to an external port 80
      # natpmp -a 192.168.1.1 8080 80
Add mapping from a local port 8080 to an external port 80 with lifetime of a one minute
      # natpmp -a 192.168.1.1 8080 80 -l 60
Delete mapping from a local port 8080 to an external port 80
      # natpmp -d 192.168.1.1 8080 80
</pre>
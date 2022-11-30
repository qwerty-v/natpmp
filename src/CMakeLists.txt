project(natpmp)

add_executable(natpmp
        main.c
        nat_pmp.c nat_pmp.h
        options.c options.h
        socket.c socket.h)
# Fundamental Low-Level C Projects

A collection of C projects built primarily to learn low-level programming and understand how computers work underneath higher-level abstractions.

Low-level programming is a big hobby of mine. These projects aren't intended to be production software; they're exercises for understanding things like memory management, pointers, data structures, I/O, and how data is represented and manipulated in memory.

This repository is essentially my playground for learning C from the ground up.

## Current Builds

| Project                      |               Time |
| ----------------------------- | ------------------: |
| Fixed Array                   |            ~2 hours |
| Dynamic Array                 |            ~3 hours |
| Singly Linked List            |            ~4 hours |
| Doubly Linked List            |            ~4 hours |
| Linked List Menu              |            ~4 hours |
| Single-Connection HTTP Server |            ~4 hours |

### Single-Connection HTTP Server

A minimal HTTP server built from raw POSIX sockets - no libraries, no frameworks. It:

* Creates a TCP socket, binds it to port `8080`, and listens for one incoming connection
* Accepts a single client connection, reads the raw HTTP request into a buffer
* Parses the request line (method, path, HTTP version) with `sscanf`
* Loads `index.html` fully into memory (`fopen`/`fseek`/`fread`)
* Constructs a valid `HTTP/1.1 200 OK` response with correct headers (`Content-Type`, `Content-Length`)
* Sends the header and body back to the client over the socket, then closes both the connection and listening sockets

This was built as a study project to understand the raw mechanics of TCP servers - `socket()` → `setsockopt()` → `bind()` → `listen()` → `accept()` → `read()`/`write()` → `close()` - before attempting a larger, concurrent HTTP server from scratch.

The time estimates are roughly how long I spent implementing and understanding each structure/project myself.

## Topics I've Learned

* Pointers
* Manual memory management
* `malloc` / `free`
* Structs
* Arrays and their underlying memory layout
* Strings
* Dynamic memory allocation
* Memory traversal
* Linked data structures
* TCP socket programming (`socket`, `bind`, `listen`, `accept`)
* Raw HTTP request/response handling over sockets
* Reading files into memory and building responses with correct headers

## Next Builds

* Hash tables
* [Least Recently Used (LRU) cache](https://en.wikipedia.org/wiki/Cache_replacement_policies#LRU)
* Binary trees
* Concurrent HTTP server (thread-per-connection, then an `epoll`-based event loop) - a full ~1.5–2k line C server supporting multiple simultaneous connections, real HTTP/1.1 parsing, static file serving with directory-traversal protection, keep-alive, timeouts, and logging
* More data structures and low-level experiments

## Resources

### C & Low-Level Programming

* [Core Dumped](https://www.youtube.com/@CoreDumpped/videos) - C and low-level programming
* [Ben Eater](https://www.youtube.com/@BenEater) - Computer architecture and electronics
* [How a Computer Works - From Silicon to Apps](https://www.youtube.com/watch?v=5f3NJnvnk7k)

### Data Structures

* [GeeksforGeeks - Linked Lists in C](https://www.geeksforgeeks.org/c/how-to-create-a-linked-list-in-c/)

### Memory Allocation

* [A Malloc Tutorial](https://danluu.com/malloc-tutorial/) - Understanding how `malloc` works

### Networking

* [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/) - the classic reference for sockets in C

---

**Goal:** Build these structures myself, understand how they work, and eventually understand enough about the underlying systems to implement more complex low-level projects.

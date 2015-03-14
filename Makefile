

all:
	echo dijkstra,rbtree,mergesort,quicksort,234tree,median_finder,selection_sort,insertion_sort,avltree,stack,queue,hashmap bfs

string_rotate: string_rotate.cc utils.h
	gfilt -banner:N /cand:L -g string_rotate.cc -o $@

bfs: bfs.cc utils.h
	gfilt -banner:N /cand:L -g bfs.cc -o $@

rbtree: rbtree.cc utils.h
	gfilt -banner:N /cand:L -g rbtree.cc -o $@

quicksort: quicksort.cc utils.h
	gfilt -banner:N /cand:L -g quicksort.cc -o $@

mergesort: mergesort.cc utils.h
	gfilt -banner:N /cand:L -g mergesort.cc -o $@

selection_sort: selection_sort.cc utils.h
	gfilt -banner:N /cand:L -g selection_sort.cc -o $@

insertion_sort: insertion_sort.cc utils.h
	gfilt -banner:N /cand:L -g insertion_sort.cc -o $@

median_finder: median_finder.cc utils.h
	gfilt -banner:N /cand:L -g median_finder.cc -o $@

heapsort: heapsort.cc utils.h
	gfilt -banner:N /cand:L -g heapsort.cc -o $@

234tree: 234tree.cc utils.h
	gfilt -banner:N /cand:L -g 234tree.cc -o $@

dijkstra: dijkstra.cc utils.h
	gfilt -banner:N /cand:L -g dijkstra.cc -o $@

avltree: avltree.cc utils.h
	gfilt -banner:N /cand:L -g avltree.cc -o $@

stack: stack.cc utils.h
	gfilt -banner:N /cand:L -g stack.cc -o $@

queue: queue.cc utils.h
	gfilt -banner:N /cand:L -g queue.cc -o $@

hashmap: hashmap.cc utils.h
	gfilt -banner:N /cand:L -g hashmap.cc -o $@

clean:
	rm *.o a.out heapsort dijkstra 234tree median_finder insertion_sort selection_sort mergesort quicksort rbtree avltree stack queue hashmap bfs



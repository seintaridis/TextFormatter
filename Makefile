#
# In order to execute this "Makefile" just type "make"
#	A. Delis (ad@di.uoa.gr)
#





OBJS 	= splitter.o exclusive.o splitter_impl.o readwrite.o
OBJS1	=root.o readwrite.o builder_list.o
OBJS2	=builder.o builder_list.o readwrite.o
SOURCE	= splitter.c exclusive.c splitter_impl.c root.c readwrite.c builder_list.c
HEADER  = exclusive.h splitter.h readwrite.h builder_list.h
OUT  	=  splitter
OUT1	=  lexana
OUT2	=  builder
CC	= gcc
FLAGS   = -g -c 
# -g option enables debugging mode 
# -c flag generates object code for separate files

splitter: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files >>separately<< 
splitter.o: splitter.c
	$(CC) $(FLAGS) splitter.c

exclusive.o: exclusive.c
	$(CC) $(FLAGS) exclusive.c

splitter_impl.o:splitter_impl.c
	$(CC) $(FLAGS) splitter_impl.c

readwrite.o:readwrite.c
	$(CC) $(FLAGS) readwrite.c

builder_list.o:builder_list.c
	$(CC) $(FLAGS)builder_list.c

root: $(OBJS1)
	$(CC) -g $(OBJS1) -o $(OUT1)

root.o:root.c
	$(CC) $(FLAGS) root.c

builder: $(OBJS2)
	$(CC) -g $(OBJS2) -o $(OUT2)

builder.o:builder.c
	$(CC) $(FLAGS) builder.c

# clean house
clean:
	rm -f $(OBJS) $(OUT)
	rm -f $(OBJS1) $(OUT1)
	rm -f $(OBJS2) $(OUT2)
# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)

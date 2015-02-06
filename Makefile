DIR_NAME=prj
DOC=./doc
SRCDIR=src
BIN=bin
#prog = prj
prog = TEST
src := $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/*.c)
obj += $(subst .c,.o,$(filter %.c, $(src))) 
obj += $(subst .cpp,.o,$(filter %.cpp, $(src))) 
libs := #../ds/libds.a ../tools/obj/libobj.a

include_dir =

CFLAGS += $(addprefix -I,$(include_dir)) -g -D$(prog)
CXXFLAGS += $(CFLAGS) -std=c++11
LDFLAGS := #-L../ds/ -lds -L../tools/obj/ -lobj

All: $(prog)

run: $(BIN)/$(prog)
	echo "------ Testing ------"
	time ./$(BIN)/$(prog) 

test: $(BIN)/$(prog)
	echo "------ Test 1k edges ------"
	time ./$(BIN)/$(prog) ./test/test_graph_e1k.txt
	echo "------ Test 10k edges ------"
	time ./$(BIN)/$(prog) ./test/test_graph_e10k.txt
	echo "------ Test 100k edges ------"
	time ./$(BIN)/$(prog) ./test/test_graph_e100k.txt
	echo "------ Test 1000k edges ------"
	time ./$(BIN)/$(prog) ./test/test_graph_e1000k.txt

cases: $(BIN)/make_graph
	./$(BIN)/make_graph 1000 ./test/test_graph_e1k.txt
	./$(BIN)/make_graph 10000 ./test/test_graph_e10k.txt
	./$(BIN)/make_graph 100000 ./test/test_graph_e100k.txt
	./$(BIN)/make_graph 1000000 ./test/test_graph_e1000k.txt

$(prog): $(obj)
	$(CXX) $(CFLAGS) $^ $(LDFLAGS) -o $(BIN)/$@

%: %.c %.cpp $(libs)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
	
# make document
pdf:
	make -C $(DOC)

# make archived file for submit
zip:
	zip -r cs516$(prog).zip ../$(DIR_NAME) ../ds ../tools

clean:
	rm $(obj)
	rm $(DIR_NAME).zip
	rm $(BIN)/$(prog)

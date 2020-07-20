SOURCE:=server_can_selection.cpp utils/zk_base.cpp
OBJ:=server_can_selection.o zk_base.o
TARGET:=res

CC:= g++
#链接库
# LDFLAGS:=
#需要调用的链接库-lpthread
LIBS:=-DTHREADED  -lpthread -lzookeeper_mt 
DEFINES:=
#头文件
INCLUDE:=-I/usr/local/include/zookeeper
#c选项 -g等
CFLAGS:= -Wall
#cpp选项
CXXFLAGS:= 

$(TARGET):$(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)
	
$(OBJ):$(SOURCE)
	$(CC) $(INCLUDE) -c $^



.PHONY:clean

clean:
	@echo "clear project"
	rm	-rf	$(TARGET)
	rm -rf *.o
	@echo "clear compelete"
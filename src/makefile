SOURCE:=server_can_selection.cpp utils/zk_base.cpp
OBJ:=server_can_selection.o zk_base.o
TARGET:=res

CC:= g++
#���ӿ�
# LDFLAGS:=
#��Ҫ���õ����ӿ�-lpthread
LIBS:=-DTHREADED  -lpthread -lzookeeper_mt 
DEFINES:=
#ͷ�ļ�
INCLUDE:=-I/usr/local/include/zookeeper
#cѡ�� -g��
CFLAGS:= -Wall
#cppѡ��
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
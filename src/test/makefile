SOFA_PBRPC=/Users/cwh/home/pbrpc/output
PROTOBUF_DIR=/usr/local

OPT ?= -O2        # (A) Production use (optimized mode)
# OPT ?= -g2      # (B) Debug mode, w/ full line-level debugging symbols
# OPT ?= -O2 -g2  # (C) Profiling mode: opt, but w/debugging symbols
#-----------------------------------------------

CXX=g++
INCPATH=-I$(SOFA_PBRPC)/include -I$(PROTOBUF_DIR)/include \
		 -I$(ZLIB_DIR)/include 
CXXFLAGS += $(OPT) -pipe -W -Wall -fPIC -D_GNU_SOURCE -D__STDC_LIMIT_MACROS \
			$(INCPATH) -I/usr/local/include/zookeeper -I/Users/cwh/home/pbrpc/src/sofa/pbrpc \
			-std=c++11 -stdlib=libc++

LIBRARY=$(SOFA_PBRPC)/lib/libsofa-pbrpc.a $(PROTOBUF_DIR)/lib/libprotobuf.a 
LDFLAGS +=  -lpthread -lz -DTHREADED  -lzookeeper_mt  -L/usr/local/lib -lhiredis -DGTEST -lgtest -lgmock

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LDFLAGS += -lrt
else
    ifeq ($(UNAME_S),Darwin)
		LDFLAGS += -undefined dynamic_lookup
    endif
endif

PROTO_SRC=../utils/echo_service.proto 
# ��ʽ��$(patsubst <pattern>,<replacement>,<text> ) 
# ���ƣ�ģʽ�ַ����滻��������patsubst��
# ���ܣ�����<text>�еĵ��ʣ������ԡ��ո񡱡���Tab���򡰻س��������С��ָ����Ƿ����ģʽ<pattern>��
# ���ƥ��Ļ�������<replacement>�滻�����<pattern>���԰���ͨ�����%������ʾ���ⳤ�ȵ��ִ���
# ���<replacement>��Ҳ������%������ô��<replacement>�е������%������<pattern>�е��Ǹ���%�����������ִ����������á�\����ת�壬�ԡ�\%������ʾ��ʵ����ġ�%���ַ���
# ���أ��������ر��滻������ַ�����
PROTO_OBJ=$(patsubst %.proto,%.pb.o,$(PROTO_SRC))
PROTO_OPTIONS=--proto_path=. --proto_path=$(SOFA_PBRPC)/include --proto_path=$(PROTOBUF_DIR)/include

BIN=test

all: $(BIN)

.PHONY:  clean

rebuild: clean all

test: $(PROTO_OBJ) zk_base_test.o ../utils/zk_base.o 
	$(CXX) $^ -o $@ $(LIBRARY) $(LDFLAGS)

%.pb.o: %.pb.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.pb.cc: %.proto
	$(PROTOBUF_DIR)/bin/protoc $(PROTO_OPTIONS) --cpp_out=. $<

%.o: %.cc  $(PROTO_OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(BIN) *.o *.pb.* utils/*.o utils/*.out

SOFA_PBRPC=/Users/cwh/home/pbrpc/output
PROTOBUF_DIR=/usr/local

OPT ?= -O2        # (A) Production use (optimized mode)
# OPT ?= -g2      # (B) Debug mode, w/ full line-level debugging symbols
# OPT ?= -O2 -g2  # (C) Profiling mode: opt, but w/debugging symbols
#-----------------------------------------------


include /Users/cwh/home/pbrpc/depends.mk

CXX=g++
INCPATH=-I$(SOFA_PBRPC)/include -I$(PROTOBUF_DIR)/include \
		-I$(SNAPPY_DIR)/include -I$(ZLIB_DIR)/include 
CXXFLAGS += $(OPT) -pipe -W -Wall -fPIC -D_GNU_SOURCE -D__STDC_LIMIT_MACROS $(INCPATH) -I/usr/local/include/zookeeper -I/Users/cwh/home/pbrpc/src/sofa/pbrpc

LIBRARY=$(SOFA_PBRPC)/lib/libsofa-pbrpc.a $(PROTOBUF_DIR)/lib/libprotobuf.a $(SNAPPY_DIR)/lib/libsnappy.a
LDFLAGS +=  -lpthread -lz -DTHREADED  -lzookeeper_mt  -L/usr/local/lib -lhiredis

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LDFLAGS += -lrt
else
    ifeq ($(UNAME_S),Darwin)
		LDFLAGS += -undefined dynamic_lookup
    endif
endif

PROTO_SRC=utils/echo_service.proto 
# 格式：$(patsubst <pattern>,<replacement>,<text> ) 
# 名称：模式字符串替换函数——patsubst。
# 功能：查找<text>中的单词（单词以“空格”、“Tab”或“回车”“换行”分隔）是否符合模式<pattern>，
# 如果匹配的话，则以<replacement>替换。这里，<pattern>可以包括通配符“%”，表示任意长度的字串。
# 如果<replacement>中也包含“%”，那么，<replacement>中的这个“%”将是<pattern>中的那个“%”所代表的字串。（可以用“\”来转义，以“\%”来表示真实含义的“%”字符）
# 返回：函数返回被替换过后的字符串。
PROTO_OBJ=$(patsubst %.proto,%.pb.o,$(PROTO_SRC))
PROTO_OPTIONS=--proto_path=. --proto_path=$(SOFA_PBRPC)/include --proto_path=$(PROTOBUF_DIR)/include

BIN=server client

all: $(BIN)

.PHONY:  clean

rebuild: clean all

server: $(PROTO_OBJ) server.o utils/zk_base.o utils/Redis.o
	$(CXX) $^ -o $@ $(LIBRARY) $(LDFLAGS)

client: $(PROTO_OBJ) client.o utils/zk_base.o
	$(CXX) $^ -o $@ $(LIBRARY) $(LDFLAGS)

%.pb.o: %.pb.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.pb.cc: %.proto
	$(PROTOBUF_DIR)/bin/protoc $(PROTO_OPTIONS) --cpp_out=. $<

%.o: %.cc  $(PROTO_OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(BIN) *.o *.pb.* utils/*.o utils/*.out

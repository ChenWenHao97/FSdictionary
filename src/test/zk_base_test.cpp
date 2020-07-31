#include "../utils/common.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../utils/zk_base.hpp"
// #include "bhook.h"
using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::SetArgPointee;
/*mockÀý×Ó*/
// class MockFoo : public Foo {
//  public:
//   MockFoo() {
//     // By default, all calls are delegated to the real object.
//     ON_CALL(*this, DoThis).WillByDefault([this](int n) {
//       return real_.DoThis(n);
//     });
//     ON_CALL(*this, DoThat).WillByDefault([this](const char* s, int* p) {
//       real_.DoThat(s, p);
//     });
//     ...
//   }
//   MOCK_METHOD(char, DoThis, ...);
//   MOCK_METHOD(void, DoThat, ...);
//   ...
//  private:
//   Foo real_;
// };
class Mockzkbase : public zk_base
{
public:
    Mockzkbase() : zk_base()
    {
        ON_CALL(*this, zk_init(_, _, _, _, _, _)).WillByDefault(Invoke(this, &Mockzkbase::Realinit));
    }
    MOCK_METHOD6(zk_init, zhandle_t *(const char *, watcher_fn, int, const clientid_t *, void *, int));
    zhandle_t *Realinit(const char *host, watcher_fn watcher,
                        int timeout, const clientid_t *clientid, void *context, int flags)
    {
        return zk_base::zk_init(host, watcher, timeout, clientid, context, flags);
    }
};
class zkbaseTest : public ::testing::Test
{
public:
    void SetUp()
    {
        this->zk_handle = new zk_base();
    }
    void TearDown()
    {
        delete this->zk_handle;
    }

protected:
    zk_base *zk_handle;
};
// zhandle_t* my_init(const char *host, watcher_fn watcher,
//                             int timeout, const clientid_t *clientid, void *context, int flags)
// {
//     int err;
//     int ret = fault_fail("zk_base::zk_init".&err);
//     if(ret == 0)
//     {
// 		printf("\e[33;1m[=HOOK=] this is  hook init\n\e[m");
// 		return err;
// 	}

//     typedef int (*REAL_FUNC)(const char *host, watcher_fn watcher,
//                             int timeout, const clientid_t *clientid, void *context, int flags);
// 	REAL_FUNC old_func = (REAL_FUNC)get_real_func_lib("zk_base::zk_init");
// 	return old_func(str);

// }
TEST_F(zkbaseTest, ConstructorDestructor)
{

    EXPECT_TRUE(zk_handle->get_timeout() == 300);
    EXPECT_TRUE(zk_handle->get_flags() == 0);
    EXPECT_TRUE(zk_handle->get_clientid() == nullptr);
}
TEST_F(zkbaseTest,Init)
{
    // attach_func_lib("zk_base::zk_init",(void*)my_init);
    // fault_enable("zk_base::zk_init",100,-1);
    //Î´³É¹¦zookeeper_init
    // zk_base* handle = new zk_base();
    Mockzkbase *mymockzk = new Mockzkbase();
    EXPECT_CALL(*mymockzk,zk_init(_, _, _, _, _, _));

    // EXPECT_TRUE(mymockzk->zk_init(_, _, _, _, _, _) == NULL);

    //success
    int zkhandle = 5;
    // EXPECT_CALL(*zk_handle, zk_init(_, _, _, _, _, _)).WillOnce(Return((zhandle_t *)&zkhandle));
    // EXPECT_TRUE(zk_handle->zk_init(_, _, _, _, _, _) != NULL);
    delete mymockzk;
}

int main(int argc, char *argv[])
{

  ::testing::GTEST_FLAG(throw_on_failure) = true;
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

/* to use tests write:
* UNIT_TEST(magic_add, two_plus_two)
* {
*		int a = MyMagicAddFunction(2, 2);
*		Assert(a == 4, "result does not equal 4");
* }
* 
* you can call Assert multiple times in single test.
*/

#define UNIT_TEST(category, name) \
class test_##category##_##name : public Test \
{	\
public:	\
	test_##category##_##name() : Test(#category, #name) {};	\
	virtual void OnExecute() override;	\
};	\
test_##category##_##name g_test_##category##_##name;\
void test_##category##_##name::OnExecute()

// all tests derive from that
class Test
{
public:
	Test(const char* category, const char* name);
	bool Execute();

protected:
	// call Assert inside of the unit test to verify conditions
	void Assert(bool condition, const char* message);

	// this is where the test is executed
	virtual void OnExecute() = 0;

private:
	const char* m_category;
	const char* m_name;
	bool m_hasPassed;
};

// call this in main function
void RunAllTests();

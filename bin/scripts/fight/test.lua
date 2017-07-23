lua_table = {1, "string", 1.0}

function run( combat )
	-- 处理来自c++创建的lua table(战斗数据)
	print_table( combat )
end


-- 测试接受C++对象
function test_object(foo_obj)
    --测试构造
    base = base_t()
	
    -- 测试C++对象函数
    foo_obj:print(12333, base)

    --基类的函数
    foo_obj:dump()
    foo_obj.a =3000
	-- 测试C++ 对象属性
    print("foo property", foo_obj.a)
    print("base property", foo_obj.v)
	print( "base property2", base.v )
end

-- 测试返回C++对象
function test_ret_object(foo_obj)
    return foo_obj
end

function return_table(arg)
	local ret = {}
	ret.name = arg
	return ret
end

clazz:static_func()
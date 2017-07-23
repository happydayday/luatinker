
#include <stdlib.h>
#include <cstring>
#include <cassert>
#include <list>
#include <set>
#include <map>
#include <vector>

#include "vec3.h"
#include "test.h"
#include "luaenv.h"

void initHero( LuaEnv * env, LuaTable & heros, int32_t pos,  uint32_t id, uint32_t level,
        const Vec3i & p, const Vec3f & s, int32_t fightDistance, int32_t nowBlood, int32_t maxBlood )
{
    heros.set( pos, LuaTable( env->luastate() ) );
    LuaTable hero = heros.get< int32_t, LuaTable>( pos );
    hero.set( "id", id );
    hero.set( "level", level );

    hero.set( "position", LuaTable( env->luastate() ) );
    LuaTable position = hero.get< const char *, LuaTable>( "position" );
    position.set( "x", p.x );
    position.set( "y", p.y );
    position.set( "z", p.z );

    hero.set( "scale", LuaTable( env->luastate() ) );
    LuaTable scale = hero.get< const char *, LuaTable>( "scale" );
    scale.set( "x", s.x );
    scale.set( "y", s.y );
    scale.set( "z", s.z );

    hero.set( "attribute", LuaTable( env->luastate() ) );
    LuaTable attribute = hero.get< const char *, LuaTable>( "attribute" );
    attribute.set( "fightDistance", fightDistance );
    attribute.set( "nowBlood", nowBlood );
    attribute.set( "maxBlood", maxBlood );

    hero.set( "skills", LuaTable( env->luastate() ) );
}

void initHeroSkill( LuaEnv * env, LuaTable & skills, int32_t pos,
        uint32_t id, uint32_t level, int32_t index, uint32_t cost )
{
    skills.set( pos, LuaTable( env->luastate() ) );
    LuaTable skill = skills.get<int32_t, LuaTable>( pos );

    skill.set( "id", id );
    skill.set( "level", level );
    skill.set( "cost", cost );
    skill.set( "roleIndex", LuaTable( env->luastate() ) );
    LuaTable roleIndex = skill.get< const char *, LuaTable>( "roleIndex" );
    roleIndex.set( 1, index );
}

void runCombat( LuaEnv * env )
{
    LuaTable combat( env->luastate() );
    combat.set( "copyid", 1001 );
    combat.set( "attacker", LuaTable( env->luastate() ) );
    combat.set( "defender", LuaTable( env->luastate() ) );

 
    // 攻击者    
	{
        LuaTable attacker = combat.get< const char *, LuaTable>( "attacker" );
        attacker.set( "heros", LuaTable( env->luastate() ) );
        // 伙伴列表 heros={{"id":10001, "level":1, "position":{}, "scale":{}, "attribute":{}}, ...}
            //  伙伴id
            //  伙伴等级
            //  出场位置
            //  伙伴scale
            //  伙伴属性attribute={ "fightDistance":5, "nowBlood":1,"maxBlood":1,...}
            //  伙伴技能skills={{"id":100013, "level":1002, "index":{}, "cost":1},...}
        LuaTable heros = attacker.get< const char *, LuaTable>( "heros" );
        {
            // 初始化伙伴数据            
			initHero( env, heros, 1, 10001, 1, Vec3i( -25,0,0 ), Vec3f(2.5,2.5,2.5), 5, 2500, 2500 );

            // 初始化伙伴技能卡数据
            LuaTable hero = heros.get< int32_t, LuaTable>( 1 );
            LuaTable skills = hero.get< const char *, LuaTable>( "skills" );
            initHeroSkill( env, skills, 1, 100013, 1, 1, 4 );
            initHeroSkill( env, skills, 2, 100014, 1, 1, 4 );
        }

        {
            initHero( env, heros, 2, 10002, 1, Vec3i(-25,0,-4), Vec3f(2.7,2.7,2.7), 4, 3000, 3000 );
            LuaTable hero = heros.get< int32_t, LuaTable>( 2 );
            LuaTable skills = hero.get< const char *, LuaTable>( "skills" );
            initHeroSkill( env, skills, 1, 100023, 1, 2, 3 );
            initHeroSkill( env, skills, 2, 100024, 1, 2, 3 );
        }

        {
            initHero( env, heros, 3, 10003, 1, Vec3i(-35,0,0), Vec3f(2,2,2), 14, 1500, 1500 );
            LuaTable hero = heros.get< int32_t, LuaTable>( 3 );
            LuaTable skills = hero.get< const char *, LuaTable>( "skills" );
            initHeroSkill( env, skills, 1, 100033, 1, 5, 4 );
            initHeroSkill( env, skills, 2, 100034, 1, 5, 4 );
        }

        {
            initHero( env, heros, 4, 10004, 1, Vec3i(-25,0,4), Vec3f(2.3,2.3,2.3), 7, 750, 750);
            LuaTable hero = heros.get< int32_t, LuaTable>( 4 );
            LuaTable skills = hero.get< const char *, LuaTable>( "skills" );
            initHeroSkill( env, skills, 2, 100043, 1, 3, 2 );
            initHeroSkill( env, skills, 1, 100044, 1, 3, 3 );
        }

        {
            initHero( env, heros, 5, 10005, 1, Vec3i(-30,0,0), Vec3f(2,2,2), 9, 2100, 2100);
            LuaTable hero = heros.get< int32_t, LuaTable>( 5 );
            LuaTable skills = hero.get< const char *, LuaTable>( "skills" );
            initHeroSkill( env, skills, 1, 100053, 1, 4, 4 );
            initHeroSkill( env, skills, 2, 100054, 1, 4, 3 );
        }
    }

	// 防御者   
	{
		LuaTable defender = combat.get< const char *, LuaTable>( "defender" );
		defender.set( "heros", LuaTable( env->luastate() ) );

		LuaTable heros = defender.get< const char *, LuaTable>( "heros" );
		{          
			initHero( env, heros, 1, 10001, 1, Vec3i(25,0,-4), Vec3f(2.5,2.5,2.5), 4, 2500, 2500 );

			LuaTable hero = heros.get< int32_t, LuaTable>( 1 );
			LuaTable skills = hero.get< const char *, LuaTable>( "skills" );
			initHeroSkill( env, skills, 1, 100013, 1, 2, 4 );
			initHeroSkill( env, skills, 2, 100014, 1, 2, 4 );
		}

		{
			initHero( env, heros, 2, 10002, 1, Vec3i(25,0,0), Vec3f(2.7,2.7,2.7), 4, 3000, 3000 );
			LuaTable hero = heros.get< int32_t, LuaTable>( 2 );
			LuaTable skills = hero.get< const char *, LuaTable>( "skills" );
			initHeroSkill(env,  skills, 1, 100023, 1, 3, 3 );
			initHeroSkill( env, skills, 2, 100024, 1, 3, 3 );
		}

		{
			initHero( env, heros, 3, 10003, 1, Vec3i(35,0,0), Vec3f(2,2,2), 14, 1500, 1500 );
			LuaTable hero = heros.get< int32_t, LuaTable>( 3 );
			LuaTable skills = hero.get< const char *, LuaTable>( "skills" );
			initHeroSkill( env, skills, 1, 100033, 1, 5, 4 );
			initHeroSkill( env, skills, 2, 100034, 1, 5, 4 );
		}

		{
			initHero( env, heros, 4, 10004, 1, Vec3i(25,0,4), Vec3f(2.3,2.3,2.3), 4, 2000, 2000);
			LuaTable hero = heros.get< int32_t, LuaTable>( 4 );
			LuaTable skills = hero.get< const char *, LuaTable>( "skills" );
			initHeroSkill( env, skills, 2, 100043, 1, 1, 2 );
			initHeroSkill( env, skills, 1, 100044, 1, 1, 3 );
		}

		{
			initHero( env, heros, 5, 10005, 1, Vec3i(30,0,0), Vec3f(2,2,2), 9, 2100, 2100);
			LuaTable hero = heros.get< int32_t, LuaTable>( 5 );
			LuaTable skills = hero.get< const char *, LuaTable>( "skills" );
			initHeroSkill( env, skills, 1, 100053, 1, 4, 4 );
			initHeroSkill( env, skills, 2, 100054, 1, 4, 3 );
		}
	}


    int32_t result = env->invoke<int32_t>( "run", combat );
}


int main()
{
	LuaEnv * env = new LuaEnv( "scripts/battle.lua" );
	env->initialize();

	// c++函数lua调用
	foo_t * f = new foo_t( 2 );
	env->invoke<bool>( "test_object", f );

	assert(f == env->invoke<foo_t*>("test_ret_object", f));
	delete f;

	LuaTable from_lua_table ( env->luastate(), "lua_table" );
	printf ( "lua_table[2] = %d\n", from_lua_table.get<int, int> ( 4 ) );

	env->invoke<void>( "print_table", from_lua_table );
	from_lua_table.set( "kkk", 100 );
	env->invoke<void>( "print_table", from_lua_table );

	luatinker::table ret = env->invoke<luatinker::table> ( "return_table", "give me a table !!" );
	printf ( "ret.name =\t%s\n", ret.get<const char *, const char*> ( "name" ) );

	// 传给lua战斗数据执行战斗脚本
	runCombat( env );
	
	system("pause");
    return 1;
}

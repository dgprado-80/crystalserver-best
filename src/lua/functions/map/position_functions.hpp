////////////////////////////////////////////////////////////////////////
// Crystal Server - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////

#pragma once

class PositionFunctions {
public:
	static void init(lua_State* L);

private:
	static int luaPositionCreate(lua_State* L);
	static int luaPositionAdd(lua_State* L);
	static int luaPositionSub(lua_State* L);
	static int luaPositionCompare(lua_State* L);

	static int luaPositionGetDistance(lua_State* L);
	static int luaPositionGetPathTo(lua_State* L);
	static int luaPositionIsSightClear(lua_State* L);

	static int luaPositionGetTile(lua_State* L);
	static int luaPositionGetZones(lua_State* L);

	static int luaPositionSendMagicEffect(lua_State* L);
	static int luaPositionRemoveMagicEffect(lua_State* L);
	static int luaPositionSendDistanceEffect(lua_State* L);

	static int luaPositionSendSingleSoundEffect(lua_State* L);
	static int luaPositionSendDoubleSoundEffect(lua_State* L);

	static int luaPositionToString(lua_State* L);
};

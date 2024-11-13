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

#include "items/containers/container.hpp"
#include "items/containers/inbox/inbox.hpp"

class DepotLocker final : public Container {
public:
	explicit DepotLocker(uint16_t type, uint16_t size);

	std::shared_ptr<DepotLocker> getDepotLocker() override {
		return static_self_cast<DepotLocker>();
	}

	void removeInbox(const std::shared_ptr<Inbox> &inbox);

	// serialization
	Attr_ReadValue readAttr(AttrTypes_t attr, PropStream &propStream) override;

	uint16_t getDepotId() const {
		return depotId;
	}
	void setDepotId(uint16_t newDepotId) {
		this->depotId = newDepotId;
	}

	// cylinder implementations
	ReturnValue queryAdd(int32_t index, const std::shared_ptr<Thing> &thing, uint32_t count, uint32_t flags, const std::shared_ptr<Creature> &actor = nullptr) override;

	void postAddNotification(const std::shared_ptr<Thing> &thing, const std::shared_ptr<Cylinder> &oldParent, int32_t index, CylinderLink_t link = LINK_OWNER) override;
	void postRemoveNotification(const std::shared_ptr<Thing> &thing, const std::shared_ptr<Cylinder> &newParent, int32_t index, CylinderLink_t link = LINK_OWNER) override;

	bool canRemove() const override {
		return false;
	}
	bool isRemoved() override {
		return false;
	}

private:
	uint16_t depotId;
};

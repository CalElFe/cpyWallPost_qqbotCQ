#include "StatusEvent.h"

#include "Unpack.h"
#include "tool.h"
#include "event.h"

void StatusEvent::color_green() { color = ������_��; }
void StatusEvent::color_orange() { color = ������_��; }
void StatusEvent::color_red() { color = ������_��; }
void StatusEvent::color_crimson() { color = ������_���; }
void StatusEvent::color_black() { color = ������_��; }
void StatusEvent::color_gray() { color = ������_��; }

string CQ::statusEVEreturn(StatusEvent& e) {
	Unpack pack;
	string _ret = pack.add(e.data).add(e.dataf).add(e.color).getAll();
	_ret = base64_encode(_ret);
	return _ret;
}

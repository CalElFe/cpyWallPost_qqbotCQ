#include "StatusEvent.h"

#include "Unpack.h"
#include "tool.h"
#include "event.h"

void StatusEvent::color_green() { color = Ðü¸¡´°_ÂÌ; }
void StatusEvent::color_orange() { color = Ðü¸¡´°_³È; }
void StatusEvent::color_red() { color = Ðü¸¡´°_ºì; }
void StatusEvent::color_crimson() { color = Ðü¸¡´°_Éîºì; }
void StatusEvent::color_black() { color = Ðü¸¡´°_ºÚ; }
void StatusEvent::color_gray() { color = Ðü¸¡´°_»Ò; }

string CQ::statusEVEreturn(StatusEvent& e) {
	Unpack pack;
	string _ret = pack.add(e.data).add(e.dataf).add(e.color).getAll();
	_ret = base64_encode(_ret);
	return _ret;
}

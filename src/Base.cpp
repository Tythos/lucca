/*	Lucca static object
	Basic tools (exceptions, references, etc.)
*/

#include "../inc/Lucca.h"

namespace Lucca {
	const char* xUnknown::what() const throw() {
		return "Some kind of unknown astrodynamics exception was thrown";
	}
}

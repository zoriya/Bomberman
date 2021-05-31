/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** TraceLog
*/

#ifndef TRACELOG_HPP_
#define TRACELOG_HPP_

#include <raylib.h>

namespace RAY {
	class TraceLog {
		public:
			typedef ::TraceLogLevel Level;

			//! @brief Set Trace Log level
			//! @param level Level of log to display
			static void setLevel(Level level);
	};
}

#endif /* !TRACELOG_HPP_ */

/*
  * Copyright (C) 2013 Cameron White
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ACTIONS_ADDREHEARSALSIGN_H
#define ACTIONS_ADDREHEARSALSIGN_H

#include <QUndoCommand>
#include <score/rehearsalsign.h>
#include <score/scorelocation.h>

/// Adds a new rehearsal sign.
class AddRehearsalSign : public QUndoCommand
{
public:
    AddRehearsalSign(const ScoreLocation &location,
                      const std::string &description);

    virtual void redo() override;
    virtual void undo() override;

private:
    ScoreLocation myLocation;
    const std::string myDescription;
};

/// Edits an existing rehearsal sign.
class EditRehearsalSign : public QUndoCommand
{
public:
    EditRehearsalSign(const ScoreLocation &location,
                      const std::string &new_description);

    virtual void redo() override;
    virtual void undo() override;

private:
    ScoreLocation myLocation;
    const std::string myNewDescription;
    RehearsalSign myOrigSign;
};

#endif

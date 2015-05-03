Please update thsi file as development continues.

Work that is done can be moved into the pre_prod folder.

This shpuld all be done under RCS eventually.


23/6/2012
Current work is in file_read directory.
This has a frame class with associated functions.

24/6/2012
Current work is around creating a UE list with SINR measurements in each TTI.


5/7/2012
Current work is creating the queues from which the relay nodes and eNodeB can
transmit to the UEs

Have been able to assign a vector to another vector.  The vector has frames as
it's element.

Only issue will be if the frame class changes.

Next work is to create the TX and RX queues.  This may be easier now that we
now how to do Farme Queues.

7/7/2012
Created a program to read in a list of UEs, with the time and the
instantaneous SINR.

Created a class called UserEquipment.

This is currently located in the user directory.

It will be moved to pre_prod when it has been tested.

8/7/2012

Added the UE component to the frame component.  Called the new file core.cpp.
Still have separate user and frame parts, along with separate .h files.

9/7/2012

10/7/2012

15/7/2012
Some changes have been made.  Chief among them is the use of git as the
version control system.

This file (README.txt) file will likely be brought under the same revision
control system and be moved to the the core directory.

Have now added in funtion that reads in the older mpgains file.
A further function calculates the SINR on each RB.

Next step is to work out a way to skip older frames.  I think using some
variable that checks back only 32ms prior to the current time.  

The idea is to have a working queue, rather than a massive queue that we have
to iterate through every tme we want to fin a packet to transmit.


I think the way to do this is to update the frame after transmission and put
it as transmitted.  Thius can happen after transmission.

Then, the transmission queue can be drained.

So after we transmit frames, set the flag to 1, then in the making of the
TXqueue, add in an extra part to the iff where the transmission status is
checked.

This should help in keeping the TX candidate size down.


21/7/2012
A number of changes made today, which are reflected in the git comments
section.


27/7/2012
There are goals for this coming weekend.  Main one is to start gathering data.


5/9/2012
Probably most of the info in this file is actually in the journal now.


# REII313_Practical_Steyn_VanStaden
Logic Gate Simulator by CE Steyn (30070147) and RJ van Staden (30026792) for REII 313.

Use Case Study:
* TO PLACE A GATE
  Left-Click on choice of gate located in the panel to the left
  Move your mouse to the approipriate place
  To place the gate on the schematic, Left-Click again
  You are not able to place gates on the panel
  
* TO MOVE A PLACED GATE
  Right-Click on the gate you want to move
  Move your mouse to the appropriate place
  Left-Click to place the gate on the schematic
  If wires are connected, the wires will also move with the gate
  
* TO DELETE A PLACED GATE
  Leftt-Click on the gate, you will see a shadow appear around the chosen gate
  By pressing the DELETE key on your keyboard, you can delete the gate and connected wires
  
* TO PLACE A WIRE
  Hover your mouse over a placed gate's output node.
  You will see the cursor change, showing the node is available for wire placement
  Left-Click on the node, and a wire will follow the move of the mouse
  All Input nodes of placed gates which are not conncted, will glow green
  By Left-Clicking on a green Input Node, the wire can be connected
  The Program will not accept wire placement on connected nodes
  
* TO DELETE A WIRE
  Right-Click on the wire, you will see a shadow appear around the wire
  By pressing the DELETE key on your keyboard, the wire gets deleted
  
* PULSE LOGIC GATE CHANGE PULSE PROPERTIES
  If you placed a Pulse/Clock input gate you can change the time the pulse is HIGH and LOW
  Left-Clicking on a placed PULSE gate will emit a shodow around the gate
  Pressing the SPACE bar, will open a dialog to change the time the pulse is HIGH and LOW
  The range of time is 10ms to 10s
  Input the times in ms
  
* TO START A NEW SCHEMATIC
  By Clicking on the 'New' Icon located top left of the toolbar
  You need to confirm that you want to start a new schematic
  Any unsaved progress will be removed if you proceed, the schematic will be cleared
  
* TO SAVE A SCHEMATIC
  By clicking on the 'Save' Icon located on the toolbar
  A dialog will open for you to select the folder that you want to save schematic to
  NB: The user must input the filename + .json, otherwise the file will not save
  ACCEPTED: file1.json
  REJECTED: file1
  
* TO OPEN A SCHEMATIC
  By clicking on the 'Open' Icon located on the toolbar
  Any unsaved progress will be lost if you open a saved file
  By clicking on the appropriate .json file, your schematic will load
  
  

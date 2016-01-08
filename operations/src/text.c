/*Text entry box used for the whiteboard/Operator Messages in the Operations Console Display

Created By: Mathew Hicks
Created On: September 2, 2008
Last Modified By:
Last Modified On:


*/
#include </usr/include/Xm/Xm.h>
#include </usr/include/Xm/FileSB.h>
#include </usr/include/Xm/Text.h>
#include <stdio.h>
#include <stdlib.h>

//Global variables
XtAppContext app;
Widget toplevel, text;  //Top window and the actual text box widget
char *filename; 	//This is the filename of the file that the text box gets info from and writes data to.
char *filetext;		//The string contents of the file when opening it
long len;

//Method declaration
//
// -- This method is the callback, called when any character is changed, added, or deleted
//	code for this method is at the end of the file
void changesave_callback(Widget text, XtPointer client_data, XtPointer call_data);

//Main 
int main(argc,argv)
 int argc;
 char *argv[];
{

//X11 variables
Arg al[10];	//Holds arguments to be passed to X-Objects
int ac;		//Index for the arguments array 
Colormap cmap;
XColor color;

//Font variables
XFontStruct *font=NULL;
XmFontList fontlist=NULL;
char *namestring = NULL;

//File read variables
FILE  *fp;
long lSize;
size_t result;


//
//This section gets the info from the whiteboard file and loads it into a buffer that will
//load into the text display during initialization. 
//
filename = "/usr/local/cnts/epics/operations/var/whiteboard.txt";
fp = fopen (filename, "r");
// obtain file size:
fseek (fp , 0 , SEEK_END);
lSize = ftell (fp);
rewind (fp);
// allocate memory to contain the whole file:
filetext = (char*) (malloc (sizeof(char)*lSize));
if (filetext == NULL) {printf ("Memory error"); exit (0);}
// copy the file into the buffer:
result = fread (filetext,1,lSize,fp);
if (result != lSize) {printf ("Reading error"); exit (0);}
fread(filetext,1,5000,fp);
//closes the file it read from
fclose(fp);

//
//
//
//
//
//
//
//
//
//
//This last section of main does all the X11 drawings (main window and scrolled text entry)
//
//

//main window creation

toplevel = XtVaOpenApplication(&app, "Text", NULL,0,&argc,argv,NULL, sessionShellWidgetClass,XmNx,925,XmNy,975,XmNresizePolicy,XmRESIZE_NONE, NULL);

//scrolled text area creation
ac=0;
XtSetArg(al[ac], XmNeditMode, XmMULTI_LINE_EDIT); ac++;
XtSetArg(al[ac], XmNheight,210); ac++;
XtSetArg(al[ac], XmNwidth, 645); ac++;
//This is the problem line!
text=XmCreateScrolledText(toplevel,"text",al,ac);

XtAddCallback (text, XmNvalueChangedCallback, changesave_callback, NULL);
XtManageChild(text);

//load buffer(file text) into text window
XmTextSetString(text, filetext);

//Color management /---/ Sets the background color of the box to white
cmap = DefaultColormapOfScreen(XtScreen(toplevel));
ac=0;
color.red = (255 << 8);
color.blue = (255 << 8);
color.green = (255 << 8);
XtSetArg(al[ac],XmNbackground, (Pixel)(-1));ac++;
XtSetValues(text,al,ac);

//Change font of the text inside the text box
namestring="-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1";
font=XLoadQueryFont(XtDisplay(text),namestring);
fontlist=XmFontListCreate(font,"char_set");
ac=0;
XtSetArg(al[ac],XmNfontList,fontlist);ac++;
XtSetValues(text,al,ac);

//Draws the textbox and main window, and allows X-server to handle it
XtRealizeWidget(toplevel);
XtAppMainLoop(app);
return 0;
}

//
//
//
//
//This method is invoked when text is changed in the text window, when it is changed, it copys the new contents of the text window into a file called whiteboard.txt (the same file that is initially read from.)
void changesave_callback(Widget text, XtPointer client_data, XtPointer call_data)
{
 FILE *fp;
 fp = fopen (filename, "w");  //w means the file will be written over, not appended
 
 // saving -- get text from Text widget... 
 filetext = XmTextGetString (text);
 len = XmTextGetLastPosition (text);

 // write text to file
 fwrite (filetext, sizeof (char), len, fp);
 
 // make sure a newline terminates file 
 if (filetext[len-1] != '\n')
  fputc ('\n', fp);
 
 //closes file
 fclose(fp);
}

<map version="1.0.1">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node COLOR="#000000" CREATED="1409750716312" ID="ID_1966130693" MODIFIED="1409752120365" TEXT="Framework 3">
<font NAME="SansSerif" SIZE="20"/>
<hook NAME="accessories/plugins/AutomaticLayout.properties"/>
<node COLOR="#0033ff" CREATED="1409750740081" ID="ID_1074852789" MODIFIED="1409752120136" POSITION="right" TEXT="Linux">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409750755385" ID="ID_62293046" MODIFIED="1409752120144" TEXT="Try and work out how to build statically (using .so at the moment - perhaps should use .a?)">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750781648" ID="ID_1385338493" MODIFIED="1409752120149" POSITION="left" TEXT="GLFW">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409750789363" ID="ID_109751621" MODIFIED="1409752120153" TEXT="Start implementing a GLFW framework">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750802267" ID="ID_638009808" MODIFIED="1409752120157" POSITION="right" TEXT="Utility">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409750811084" ID="ID_1514398997" MODIFIED="1409752120159" TEXT="uber header for stdafx.h">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750822308" ID="ID_722704341" MODIFIED="1409752120164" POSITION="left" TEXT="Configuration">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409750852653" ID="ID_1529171218" MODIFIED="1409752120167" TEXT="Maybe consolidate config file and options into a single, searchable configuration?">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750825668" ID="ID_658044560" MODIFIED="1409752120171" POSITION="left" TEXT="Unit Tests">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409750879807" ID="ID_1210845573" MODIFIED="1409752120190" TEXT="probably can do nicer comparisons of strings in cvar tests now that we&apos;re using std::string">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
<node COLOR="#00b439" CREATED="1409750912056" ID="ID_971683665" MODIFIED="1409752120194" TEXT="Need to add custom log unit test">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
<node COLOR="#00b439" CREATED="1409750920568" ID="ID_538948826" MODIFIED="1409752120198" TEXT="Make unit test exe delete/create results file so that the main executable will fail to build if the unit tests fail">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
<node COLOR="#00b439" CREATED="1409751402197" ID="ID_888969038" MODIFIED="1409752120225" TEXT="Nev pointed out that CUnitTest::AddStage is poorly named - should be AddTest()">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750832716" ID="ID_1016221376" MODIFIED="1409752120227" POSITION="left" TEXT="Tracing">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409750952482" ID="ID_1515378578" MODIFIED="1409752120233" TEXT="could store callstack address of function in the trace macro? might help with debugging?">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409750981555" ID="ID_1716058498" MODIFIED="1409752120237" TEXT="requires being able to grab the callstack">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750835484" ID="ID_448037578" MODIFIED="1409752120241" POSITION="left" TEXT="File System">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409751000660" ID="ID_1602781641" MODIFIED="1409752120243" TEXT="need to handle virtual file system (mount archive (zip?) files as directories)">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
<node COLOR="#00b439" CREATED="1409751292640" ID="ID_978408760" MODIFIED="1409752120249" TEXT="need file system abstraction to control the number of open files (use boost::filesystem under the hood)">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751325681" ID="ID_926735453" MODIFIED="1409752120256" TEXT="just made a utility class in the end to wrap common functionality - how many files would I be managing anyway?">
<font NAME="SansSerif" SIZE="14"/>
</node>
<node COLOR="#990000" CREATED="1409751358003" ID="ID_175475660" MODIFIED="1409752120264" TEXT="need to factor out storage of rood directory to internal filesystem class">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750840909" ID="ID_865439110" MODIFIED="1409752120266" POSITION="left" TEXT="CVars">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409751048590" ID="ID_1804659775" MODIFIED="1409752120273" TEXT="need a way to register const vars (i.e. declared const as opposed to just flagged const)">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751225669" ID="ID_865053840" MODIFIED="1409752120280" TEXT="this is only really applicable if a constant needs to be found through the console; not sure that&apos;s ever going to be likely">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409751436246" ID="ID_1438289002" MODIFIED="1409752120288" POSITION="right" TEXT="Logs">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409751443375" ID="ID_1935149935" MODIFIED="1409752120290" TEXT="Logs no longer being elided from code when in release builds - why?">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751463960" ID="ID_1055614637" MODIFIED="1409752120291" TEXT="To do with not being able to determine the value of log_level as a constant at runtime">
<font NAME="SansSerif" SIZE="14"/>
<node COLOR="#111111" CREATED="1409751485168" ID="ID_321536859" MODIFIED="1409752120291" TEXT="release builds now expose log_level as a static constant in log.h"/>
<node COLOR="#111111" CREATED="1409751503857" ID="ID_963082408" MODIFIED="1409752120292" TEXT="once engine lifecycle management is in place, can register log level as a debug cvar"/>
<node COLOR="#111111" CREATED="1409751529515" ID="ID_508266080" MODIFIED="1409752120292" TEXT="log to file still needs implementing"/>
</node>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409751553603" ID="ID_281935706" MODIFIED="1409752120295" POSITION="right" TEXT="Issues">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409751643367" ID="ID_1167499963" MODIFIED="1409752120296" TEXT="seem to have a circular dependency for engine/independent/common/version.cpp">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751665760" ID="ID_1450754073" MODIFIED="1409752120297" TEXT="needed to remove the full path (i.e. path needed ${test_SOURCE_DIR}) of version.cpp">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
<node COLOR="#00b439" CREATED="1409751708083" ID="ID_1205031368" MODIFIED="1409752120302" TEXT="also have some smart pointer warnings in release builds">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751733611" ID="ID_449644420" MODIFIED="1409752120307" TEXT="boost include directories now treated as system directories (include_directories(SYSTEM xxx) means use -isystem instead of -I with GCC make">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
<node COLOR="#00b439" CREATED="1409751795334" ID="ID_1300026250" MODIFIED="1409752120314" TEXT="now there is separation by library, need separation by namespace">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751821111" ID="ID_51391881" MODIFIED="1409752120315" TEXT="removed interface based design">
<font NAME="SansSerif" SIZE="14"/>
<node COLOR="#111111" CREATED="1409751832448" ID="ID_199756475" MODIFIED="1409752120315" TEXT="no need for pure interfaces in static libraries or monolithic executables - it&apos;s a better fit for dynamic libraries)">
<node COLOR="#111111" CREATED="1409751863281" ID="ID_220549708" MODIFIED="1409752120316" TEXT="dynamic libraries mean all code (whether used or not) is available, and you pay the virtual dereference cost for interfaces"/>
</node>
</node>
</node>
<node COLOR="#00b439" CREATED="1409751909907" ID="ID_478044933" MODIFIED="1409752120333" TEXT="make fps calculations a separate class so that timers can have their own FPS calculator (engine can run at very high fps, but e.g. renderer is locked to 60fps">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751956661" ID="ID_1974099401" MODIFIED="1409752120336" TEXT="need to put renderer in own thread as it&apos;s dragging the engine fps down to 60fps on linux">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
<node COLOR="#00b439" CREATED="1409751988279" ID="ID_1749072372" MODIFIED="1409752120339" TEXT="work on argument parsing">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751996054" ID="ID_1074265066" MODIFIED="1409752120340" TEXT="need a generic, data driven way to parse command line (and preferably config files too)">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
<node COLOR="#00b439" CREATED="1409752025351" ID="ID_748110313" MODIFIED="1409752120352" TEXT="use a cvar for the default log flags (that way it can be overridden on either the command line or by the config file)">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
<node COLOR="#00b439" CREATED="1409752063305" ID="ID_1817448169" MODIFIED="1409752120360" TEXT="need to revisit versioning since debug builds now don&apos;t bump the version (generate_version dependencies)">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409752093019" ID="ID_1597172137" MODIFIED="1409752120363" TEXT="this might actually be a good thing - only bump the version number when there&apos;s something significant">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409814061203" ID="ID_1957547557" MODIFIED="1409814064792" POSITION="right" TEXT="Threads">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409814067467" ID="ID_1580628695" MODIFIED="1409814146467" TEXT="create a thread job class that encapsulates thread flow">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409814150504" ID="ID_1701671164" MODIFIED="1409814167876" TEXT="init() - initialise thread">
<font NAME="SansSerif" SIZE="14"/>
</node>
<node COLOR="#990000" CREATED="1409814171440" ID="ID_1712525341" MODIFIED="1409814218022" TEXT="run() - execute job">
<font NAME="SansSerif" SIZE="14"/>
</node>
<node COLOR="#990000" CREATED="1409814221594" ID="ID_907277751" MODIFIED="1409814250377" TEXT="exit() - requests job termination for a given reason">
<font NAME="SansSerif" SIZE="14"/>
<node COLOR="#111111" CREATED="1409814434371" ID="ID_1042773804" MODIFIED="1409814458808" TEXT="finished (finished job)"/>
<node COLOR="#111111" CREATED="1409814377193" ID="ID_285681085" MODIFIED="1409814431024" TEXT="break (requested)"/>
<node COLOR="#111111" CREATED="1409814390786" ID="ID_267609096" MODIFIED="1409814401759" TEXT="abort"/>
</node>
<node COLOR="#990000" CREATED="1409814254148" ID="ID_655354564" MODIFIED="1409814351277" TEXT="suspend() - suspends execution for a given amount of time (or indefinitely)">
<font NAME="SansSerif" SIZE="14"/>
</node>
<node COLOR="#990000" CREATED="1409814355224" ID="ID_403624383" MODIFIED="1409814373765" TEXT="resume() - resumes thread execution after a suspend()">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
</node>
</node>
</map>

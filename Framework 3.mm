<map version="1.0.1">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node COLOR="#000000" CREATED="1409750716312" ID="ID_1966130693" MODIFIED="1423551662597" STYLE="bubble" TEXT="Framework 3">
<font NAME="SansSerif" SIZE="20"/>
<hook NAME="accessories/plugins/AutomaticLayout.properties"/>
<node COLOR="#0033ff" CREATED="1409750740081" ID="ID_1074852789" MODIFIED="1423551630181" POSITION="right" STYLE="bubble" TEXT="Linux">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409750755385" ID="ID_62293046" MODIFIED="1423551630180" STYLE="bubble" TEXT="Try and work out how to build statically (using .so at the moment - perhaps should use .a?)">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750781648" ID="ID_1385338493" MODIFIED="1423551630180" POSITION="left" STYLE="bubble" TEXT="GLFW">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409750789363" ID="ID_109751621" MODIFIED="1423551630180" STYLE="bubble" TEXT="Start implementing a GLFW framework">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750802267" ID="ID_638009808" MODIFIED="1423551630180" POSITION="right" STYLE="bubble" TEXT="Utility">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409750811084" ID="ID_1514398997" MODIFIED="1423551630179" STYLE="bubble" TEXT="uber header for stdafx.h">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750822308" ID="ID_722704341" MODIFIED="1423551630179" POSITION="left" STYLE="bubble" TEXT="Configuration">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409750852653" ID="ID_1529171218" MODIFIED="1423551630179" STYLE="bubble" TEXT="Maybe consolidate config file and options into a single, searchable configuration?">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750825668" ID="ID_658044560" MODIFIED="1423551630179" POSITION="left" STYLE="bubble" TEXT="Unit Tests">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409750879807" ID="ID_1210845573" MODIFIED="1423551630178" STYLE="bubble" TEXT="probably can do nicer comparisons of strings in cvar tests now that we&apos;re using std::string">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
<node COLOR="#00b439" CREATED="1409750912056" ID="ID_971683665" MODIFIED="1423551630178" STYLE="bubble" TEXT="Need to add custom log unit test">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
<node COLOR="#00b439" CREATED="1409750920568" ID="ID_538948826" MODIFIED="1423551630178" STYLE="bubble" TEXT="Make unit test exe delete/create results file so that the main executable will fail to build if the unit tests fail">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
<node COLOR="#00b439" CREATED="1409751402197" ID="ID_888969038" MODIFIED="1423551630178" STYLE="bubble" TEXT="Nev pointed out that CUnitTest::AddStage is poorly named - should be AddTest()">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750832716" ID="ID_1016221376" MODIFIED="1423551630178" POSITION="left" STYLE="bubble" TEXT="Tracing">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409750952482" ID="ID_1515378578" MODIFIED="1423551630177" STYLE="bubble" TEXT="could store callstack address of function in the trace macro? might help with debugging?">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409750981555" ID="ID_1716058498" MODIFIED="1423551630177" STYLE="bubble" TEXT="requires being able to grab the callstack">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750835484" ID="ID_448037578" MODIFIED="1423551630177" POSITION="left" STYLE="bubble" TEXT="File System">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409751000660" ID="ID_1602781641" MODIFIED="1423551630177" STYLE="bubble" TEXT="need to handle virtual file system (mount archive (zip?) files as directories)">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
<node COLOR="#00b439" CREATED="1409751292640" ID="ID_978408760" MODIFIED="1423551630175" STYLE="bubble" TEXT="need file system abstraction to control the number of open files (use boost::filesystem under the hood)">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751325681" ID="ID_926735453" MODIFIED="1423551630176" STYLE="bubble" TEXT="just made a utility class in the end to wrap common functionality - how many files would I be managing anyway?">
<font NAME="SansSerif" SIZE="14"/>
</node>
<node COLOR="#990000" CREATED="1409751358003" ID="ID_175475660" MODIFIED="1423551630176" STYLE="bubble" TEXT="need to factor out storage of rood directory to internal filesystem class">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409750840909" ID="ID_865439110" MODIFIED="1423551630174" POSITION="left" STYLE="bubble" TEXT="CVars">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409751048590" ID="ID_1804659775" MODIFIED="1423551630173" STYLE="bubble" TEXT="need a way to register const vars (i.e. declared const as opposed to just flagged const)">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751225669" ID="ID_865053840" MODIFIED="1423551630174" STYLE="bubble" TEXT="this is only really applicable if a constant needs to be found through the console; not sure that&apos;s ever going to be likely">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409751436246" ID="ID_1438289002" MODIFIED="1423551630173" POSITION="right" STYLE="bubble" TEXT="Logs">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409751443375" ID="ID_1935149935" MODIFIED="1423551630172" STYLE="bubble" TEXT="Logs no longer being elided from code when in release builds - why?">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751463960" ID="ID_1055614637" MODIFIED="1423551630172" STYLE="bubble" TEXT="To do with not being able to determine the value of log_level as a constant at runtime">
<font NAME="SansSerif" SIZE="14"/>
<node COLOR="#111111" CREATED="1409751485168" ID="ID_321536859" MODIFIED="1423551630172" STYLE="bubble" TEXT="release builds now expose log_level as a static constant in log.h"/>
<node COLOR="#111111" CREATED="1409751503857" ID="ID_963082408" MODIFIED="1423551630172" STYLE="bubble" TEXT="once engine lifecycle management is in place, can register log level as a debug cvar"/>
<node COLOR="#111111" CREATED="1409751529515" ID="ID_508266080" MODIFIED="1423551630173" STYLE="bubble" TEXT="log to file still needs implementing"/>
</node>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409751553603" ID="ID_281935706" MODIFIED="1423551630172" POSITION="right" STYLE="bubble" TEXT="Issues">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409751643367" ID="ID_1167499963" MODIFIED="1423551630172" STYLE="bubble" TEXT="seem to have a circular dependency for engine/independent/common/version.cpp">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751665760" ID="ID_1450754073" MODIFIED="1423551630172" STYLE="bubble" TEXT="needed to remove the full path (i.e. path needed ${test_SOURCE_DIR}) of version.cpp">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
<node COLOR="#00b439" CREATED="1409751708083" ID="ID_1205031368" MODIFIED="1423551630171" STYLE="bubble" TEXT="also have some smart pointer warnings in release builds">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751733611" ID="ID_449644420" MODIFIED="1423551630171" STYLE="bubble" TEXT="boost include directories now treated as system directories (include_directories(SYSTEM xxx) means use -isystem instead of -I with GCC make">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
<node COLOR="#00b439" CREATED="1409751795334" ID="ID_1300026250" MODIFIED="1423551630169" STYLE="bubble" TEXT="now there is separation by library, need separation by namespace">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751821111" ID="ID_51391881" MODIFIED="1423551630169" STYLE="bubble" TEXT="removed interface based design">
<font NAME="SansSerif" SIZE="14"/>
<node COLOR="#111111" CREATED="1409751832448" ID="ID_199756475" MODIFIED="1423551630169" STYLE="bubble" TEXT="no need for pure interfaces in static libraries or monolithic executables - it&apos;s a better fit for dynamic libraries)">
<node COLOR="#111111" CREATED="1409751863281" ID="ID_220549708" MODIFIED="1423551630169" STYLE="bubble" TEXT="dynamic libraries mean all code (whether used or not) is available, and you pay the virtual dereference cost for interfaces"/>
</node>
</node>
</node>
<node COLOR="#00b439" CREATED="1409751909907" ID="ID_478044933" MODIFIED="1423551630166" STYLE="bubble" TEXT="make fps calculations a separate class so that timers can have their own FPS calculator (engine can run at very high fps, but e.g. renderer is locked to 60fps">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751956661" ID="ID_1974099401" MODIFIED="1423551630167" STYLE="bubble" TEXT="need to put renderer in own thread as it&apos;s dragging the engine fps down to 60fps on linux">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
<node COLOR="#00b439" CREATED="1409751988279" ID="ID_1749072372" MODIFIED="1423551630166" STYLE="bubble" TEXT="work on argument parsing">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409751996054" ID="ID_1074265066" MODIFIED="1423551630166" STYLE="bubble" TEXT="need a generic, data driven way to parse command line (and preferably config files too)">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
<node COLOR="#00b439" CREATED="1409752025351" ID="ID_748110313" MODIFIED="1423551630165" STYLE="bubble" TEXT="use a cvar for the default log flags (that way it can be overridden on either the command line or by the config file)">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
<node COLOR="#00b439" CREATED="1409752063305" ID="ID_1817448169" MODIFIED="1423551630164" STYLE="bubble" TEXT="need to revisit versioning since debug builds now don&apos;t bump the version (generate_version dependencies)">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409752093019" ID="ID_1597172137" MODIFIED="1423551630165" STYLE="bubble" TEXT="this might actually be a good thing - only bump the version number when there&apos;s something significant">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
<node COLOR="#00b439" CREATED="1415368664925" ID="ID_1100391884" MODIFIED="1423551630162" STYLE="bubble" TEXT="timers don&apos;t respect parents (e.g. scaled to their parents)">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1415368681740" ID="ID_1319914643" MODIFIED="1423551630162" STYLE="bubble">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      need to have another pass over timers and fix parental dependencies.
    </p>
    <p>
      also, need to rethink timer updates; child timers should update from parents (i.e. parents update children) but this could lead to difficulties as timers can have more than one child...
    </p>
  </body>
</html></richcontent>
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
<node COLOR="#00b439" CREATED="1423551569785" ID="ID_1094375034" MODIFIED="1423551630160" STYLE="bubble" TEXT="Solved">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
</node>
<node COLOR="#0033ff" CREATED="1409814061203" ID="ID_1957547557" MODIFIED="1423551630160" POSITION="right" STYLE="bubble" TEXT="Threads">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1409814067467" ID="ID_1580628695" MODIFIED="1423551630159" STYLE="bubble" TEXT="create a thread job class that encapsulates thread flow">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1409814150504" ID="ID_1701671164" MODIFIED="1423551630160" STYLE="bubble" TEXT="init() - initialise thread">
<font NAME="SansSerif" SIZE="14"/>
</node>
<node COLOR="#990000" CREATED="1409814171440" ID="ID_1712525341" MODIFIED="1423551630160" STYLE="bubble" TEXT="run() - execute job">
<font NAME="SansSerif" SIZE="14"/>
</node>
<node COLOR="#990000" CREATED="1409814221594" ID="ID_907277751" MODIFIED="1423551630160" STYLE="bubble" TEXT="exit() - requests job termination for a given reason">
<font NAME="SansSerif" SIZE="14"/>
<node COLOR="#111111" CREATED="1409814434371" ID="ID_1042773804" MODIFIED="1423551630160" STYLE="bubble" TEXT="finished (finished job)"/>
<node COLOR="#111111" CREATED="1409814377193" ID="ID_285681085" MODIFIED="1423551630160" STYLE="bubble" TEXT="break (requested)"/>
<node COLOR="#111111" CREATED="1409814390786" ID="ID_267609096" MODIFIED="1423551630160" STYLE="bubble" TEXT="abort"/>
</node>
<node COLOR="#990000" CREATED="1409814254148" ID="ID_655354564" MODIFIED="1423551630160" STYLE="bubble" TEXT="suspend() - suspends execution for a given amount of time (or indefinitely)">
<font NAME="SansSerif" SIZE="14"/>
</node>
<node COLOR="#990000" CREATED="1409814355224" ID="ID_403624383" MODIFIED="1423551630160" STYLE="bubble" TEXT="resume() - resumes thread execution after a suspend()">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
</node>
<node COLOR="#0033ff" CREATED="1415289404165" ID="ID_593453972" MODIFIED="1423551630158" POSITION="right" STYLE="bubble" TEXT="Time">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1415289408009" ID="ID_1603589624" MODIFIED="1423551630158" STYLE="bubble" TEXT="create primary engine timer with scale of 1 that tracks engine elapsed time">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
</node>
</node>
<node COLOR="#0033ff" CREATED="1418225971523" ID="ID_923984" MODIFIED="1423551630158" POSITION="right" STYLE="bubble" TEXT="Rendering">
<edge STYLE="sharp_bezier" WIDTH="8"/>
<font NAME="SansSerif" SIZE="18"/>
<node COLOR="#00b439" CREATED="1418225977508" ID="ID_1766515701" MODIFIED="1423551630158" STYLE="bubble" TEXT="decouple physical display size from render target size">
<edge STYLE="bezier" WIDTH="thin"/>
<font NAME="SansSerif" SIZE="16"/>
<node COLOR="#990000" CREATED="1418225998012" ID="ID_949446360" MODIFIED="1423551630158" STYLE="bubble" TEXT="should allow for dynamic up/down scaling to maintain framerate">
<font NAME="SansSerif" SIZE="14"/>
</node>
</node>
</node>
</node>
</map>

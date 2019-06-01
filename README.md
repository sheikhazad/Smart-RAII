# Smart-RAII
This is to demonstrates how shared_ptr can be smart enough to use as RAII in different scenarios other than just memory management.    
In this demo, we use it for closing file descriptor in normal and exception conditions.

1. RAII for file, file will be closed in normal flow and exception.
2. RAII enables us to avoid exception handling just to close file.
3. shared_ptr will never call it's own deleter but will be replaced by local lambda function provided.
4. So, File object is never deleted by shared_ptr but closed only.
5. File object will be deleted only when it goes out of scope but not by smart_ptr - shared_ptr.
6. It also shows how try-catch can be used in constructor to inform client that object creation has failed

from BaseHTTPServer import HTTPServer, BaseHTTPRequestHandler;
import urlparse

import inspect
import json
from pprint import pprint

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        query = urlparse.urlparse(self.path).query
        params = urlparse.parse_qs(query)

        params_obj_type = type(params)
        self.wfile.write(str(params_obj_type) + " " + json.dumps(params))


def run(server_class=HTTPServer, handler_class=MyHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()


def func_info(func):
    '''showcase a way to find function information
        Argument: 'func' is the function object
    '''
    s = "\n\n" + '='*20
    e = '='*20

    print s + func.__name__ + ": source/binary file path" + e
    print inspect.getfile(func)

    print s + func.__name__ + ": docstring" + e
    print inspect.getdoc(func)

    #we can check the return value type here
    #is there a better way
    print s + func.__name__ + ": source code" + e
    print inspect.getsource(func)

    #this can only get the compiled bytecode
    #func.func_code.co_code


if __name__ == "__main__":

    #to see what functions urlparse have
    #urlparse is supposed to be a module
    print "\n\nfunctions of urlparse"
    pprint(inspect.getmembers(urlparse, inspect.isfunction))

    #to see what methods urlparse have
    #urlparse is supposed to be a class
    print "\n\nmethods of urlparse"
    pprint(inspect.getmembers(urlparse, inspect.ismethod))

    #to see all members of urlparse
    #to much output
    #pprint(inspect.getmembers(urlparse))

    #show function info
    func_info(urlparse.parse_qs)

    run()

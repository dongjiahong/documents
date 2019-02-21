# Test-nginx

`test-nginx`模块需要`cpan`的支持，这里cpan的安装如下：

* 安装perl
* 下载[Test-Nginx-0.25](http://search.cpan.org/CPAN/authors/id/A/AG/AGENT/Test-Nginx-0.25.tar.gz)
* cd Test-Nginx-0.25 && perl Makefile.PL
* make
* cpan Test::Nginx::Socket

如果想要使用test-nginx还需要使用依赖项[test-nginx](https://github.com/openresty/test-nginx)

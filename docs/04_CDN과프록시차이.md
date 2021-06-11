# CDN 과 프록시 차이

Contents Delivery Network

[링크](http://i5on9i.blogspot.com/2014/05/cdn-proxy-server.html)

- CDN 은 Web Cache 의 응용이다.
- Web cache 를 제공하는 proxy server 를 구성한 network 가 CDN
    - 여러대의 Proxy server 가 합쳐져서 유기적으로 web cache가 관리가 되는 게 CDN

## CDN 의 동작

시나리오: http://home.net 홈페이지에 접속한다.

동작 전 상태 :

http://home.net 의 이미지를 받으려고 CDN 서비스에서 서버주소를 하나 받고, 그곳에 이미지를 올려놓은 상태.

- CDN 의 서비스에서 받은 오리지널 서버주소가 http://cdn.net 이면, 이미지의 주소는 http://cdn.net/1.jpg 가 된다.

사전 동작:

1. user 가 web browser 를 통해 page 를 http://home.net 이라는 domain 에 mapping 된 ip 주소를 찾아가서 page 를 가져온다.

2. 그 page 에 있는 이미지 url 을 보고 image 를 가져온다.

3. 이미지 url 은 http://cdn.net/1.jpg 로 되어 있어서 web browser 는 http://cdn.net 으로 request 를 날리는 데, 이 때부터 CDN 서비스가 작동한다.

동작:

1. http://cdn.net/1.jpg 로 들어온 DNS query 를 어떤 ip address 로 mapping 해주는 가로 reverse proxy server 에 접속하게 된다.

2. 이 proxy server 에서 cache 가 존재하는 지 체크하고 file 이 존재하지 않으면 origin server 로 caching, 만약 file cache 가 존재하면 보내준다.

3. http://home.net 의 page 에 대해서도 cache 를 사용할 수 있지만, cahce miss 가 날 확률이 높아 전체적으로는 caching 하지 않는다.
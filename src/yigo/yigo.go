package yigo

import ()

type YiTick struct {
	times    uint32            // tick times
	weight   int16             // weight
	interval uint32            // millisecond
	timeout  uint32            // millisecond
	args     interface{}       // args fo do
	do       func(interface{}) // tick function
}

//type YiTick interface {
//	do(ctx TTDo)
//}

func YiGo(times uint32, weight int16, interval int32) {
}

func YiGoOnce(weight int16, interval int32) {
}

func TYiGoForever(weight int16, interval int32) {
}

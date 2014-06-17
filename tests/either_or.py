import nose
import functools

_either_or_map = dict()

def either_or(key='default', expected_failures=1):
    def either_or_decorator(test):
        
        global _either_or_map

        if not key in _either_or_map:
            _either_or_map[key] = {
                'failed': 0,
                'total': 0,
                'run': 0
            }

        metrics = _either_or_map[key]
        metrics['total'] += 1

        @functools.wraps(test)
        def inner(*args, **kwargs):
            try:
                metrics['run'] += 1
                test(*args, **kwargs)
            except Exception:
                metrics['failed'] += 1
                raise nose.SkipTest
            finally:
                if metrics['run'] == metrics['total']:
                    if metrics['failed'] > expected_failures:
                        raise Exception("More failures than expected in either_or set '%s'" % (key,))
                    elif metrics['failed'] < expected_failures:
                        raise Exception("Fewer failures than expected in either_or set '%s'" % (key,))

        return inner
    return either_or_decorator
